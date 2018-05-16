#include "util.h"

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/bcm.h>

#define PROGNAME "socketcan-bcm-demo"
#define VERSION  "1.0.0"

#define MSGID   (0x0BC)
#define NFRAMES (1)

#define DELAY (10000)

static sig_atomic_t sigval;

static void onsig(int val)
{
    sigval = (sig_atomic_t)val;
}

static void usage(void)
{
    puts("Usage: " PROGNAME "[OPTIONS] IFACE\n"
         "Where:\n"
         "  IFACE    CAN network interface\n"
         "Options:\n"
         "  -h       Display this help then exit\n"
         "  -v       Display version info then exit\n");
}

static void version(void)
{
    puts(PROGNAME " " VERSION "\n");
}

void print_can_frame(const struct can_frame * const frame)
{
    const unsigned char *data = frame->data;
    const unsigned int dlc = frame->can_dlc;
    unsigned int i;

    printf("%03X  [%u] ", frame->can_id, dlc);
    for (i = 0; i < dlc; ++i)
    {
        printf(" %02X", data[i]);
    }
}

int main(int argc, char **argv)
{
    int flags, opt;
    int s;
    char *iface;
    struct sockaddr_can addr;
    struct ifreq ifr;
    
    struct can_msg
    {
        struct bcm_msg_head msg_head;
        struct can_frame frame[NFRAMES];
    } msg;

    /* Check if at least one argument was specified */
    if (argc < 2)
    {
        fputs("Too few arguments!\n", stderr);
        usage();
        return EXIT_FAILURE;
    }

    /* Parse command line options */
    while ((opt = getopt(argc, argv, "hv")) != -1)
    {
        switch (opt)
        {
        case 'h':
            usage();
            return EXIT_SUCCESS;
        case 'v':
            version();
            return EXIT_SUCCESS;
        default:
            usage();
            return EXIT_FAILURE;
        }
    }

    /* Exactly one command line argument must remain; the interface to use */
    if (optind == (argc - 1))
    {
        iface = argv[optind];
    }
    else
    {
        fputs("Only one interface may be used!\n", stderr);
        usage();
        return EXIT_FAILURE;
    }

    /* Register signal handlers */
    if (signal(SIGINT, onsig)    == SIG_ERR ||
        signal(SIGTERM, onsig)   == SIG_ERR ||
        signal(SIGCHLD, SIG_IGN) == SIG_ERR)
    {
        perror(PROGNAME);
        return errno;
    }

    /* Open the CAN interface */
    s = socket(PF_CAN, SOCK_DGRAM, CAN_BCM);
    if (s < 0)
    {
        perror(PROGNAME ": socket");
        return errno;
    }

    strncpy(ifr.ifr_name, iface, IFNAMSIZ);
    if (ioctl(s, SIOCGIFINDEX, &ifr) < 0)
    {
        perror(PROGNAME ": ioctl");
        return errno;
    }

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror(PROGNAME ": connect");
        return errno;
    }

    /* Set socket to non-blocking */
    flags = fcntl(s, F_GETFL, 0);
    if (flags < 0)
    {
        perror(PROGNAME ": fcntl: F_GETFL");
        return errno;
    }

    if (fcntl(s, F_SETFL, flags | O_NONBLOCK) < 0)
    {
        perror(PROGNAME ": fcntl: F_SETFL");
        return errno;
    }

    /* Setup code */
    sigval = 0;

    msg.msg_head.opcode  = RX_SETUP;
    msg.msg_head.can_id  = 0x123;
    msg.msg_head.flags   = 0;
    msg.msg_head.nframes = 0;
    if (write(s, &msg, sizeof(msg)) < 0)
    {
        perror(PROGNAME ": write: RX_SETUP");
        return errno;
    }

    /* Main loop */
    while (0 == sigval)
    {
        ssize_t nbytes;

        /* Read from the CAN interface */
        nbytes = read(s, &msg, sizeof(msg));
        if (nbytes < 0)
        {
            if (errno != EAGAIN)
            {
                perror(PROGNAME ": read");
            }

            usleep(DELAY);
        }
        else if (nbytes < (ssize_t)sizeof(msg))
        {
            fputs(PROGNAME ": read: incomplete BCM message\n", stderr);
            usleep(DELAY);
        }
        else
        {
            struct can_frame * const frame = msg.frame;
            unsigned char * const data = frame->data;
            const unsigned int dlc = frame->can_dlc;
            unsigned int i;

            /* Print the received CAN frame */
            printf("RX:  ");
            print_can_frame(frame);
            printf("\n");

            /* Modify the CAN frame to use our message ID */
            frame->can_id = MSGID;
            
            /* Increment the value of each byte in the CAN frame */
            for (i = 0; i < dlc; ++i)
            {
                data[i] += 1;
            }

            /* Set a TX message for sending this frame once */
            msg.msg_head.opcode  = TX_SEND;
            msg.msg_head.can_id  = 0;
            msg.msg_head.flags   = 0;
            msg.msg_head.nframes = 1;

            /* Write the message out to the bus */
            nbytes = write(s, &msg, sizeof(msg));
            if (nbytes < 0)
            {
                perror(PROGNAME ": write: TX_SEND");
            }
            else if (nbytes < (ssize_t)sizeof(msg))
            {
                fputs(PROGNAME ": write: incomplete BCM message\n", stderr);
            }
            else
            {
                /* Print the transmitted CAN frame */
                printf("TX:  ");
                print_can_frame(frame);
                printf("\n");
            }
        }
    }

    puts("\nGoodbye!");

    /* Close the CAN interface */
    if (close(s) < 0)
    {
        perror(PROGNAME ": close");
        return errno;
    }

    return EXIT_SUCCESS;
}