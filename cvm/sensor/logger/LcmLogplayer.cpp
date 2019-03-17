#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include <string>
#include <sstream>

#include <lcm/lcm-cpp.hpp>

#include <cvm/base/Logging.h>
#include <cvm/base/NonCopyable.h>

namespace cvm
{

namespace sensor
{

namespace logger
{

class Player : public base::NonCopyable
{
public:
    Player(int verbose,
           const std::string& lcmUrlIn,
           const std::string& lcmUrlOut,
           const std::string& channel);
    ~Player();
    void loop();

private:
    void handler(const lcm::ReceiveBuffer* rbuf, const std::string& channel);

    lcm::LCM _lcmIn;
    lcm::LCM _lcmOut;
    int _verbose;
};

Player::Player(int verbose,
               const std::string& lcmUrlIn,
               const std::string& lcmUrlOut,
               const std::string& channel)
    : _verbose(verbose),
      _lcmIn(lcmUrlIn),
      _lcmOut(lcmUrlOut)
{

    if (!_lcmOut.good() || !_lcmIn.good()) {
        DIE("Error: Failed to create LCM\n");
    }

    _lcmIn.subscribe(channel, &Player::handler, this);

}

Player::~Player()
{

}

void Player::loop()
{
    while (!_lcmIn.handle()) {
        ;
    }
}

void Player::handler(const lcm::ReceiveBuffer *rbuf,
                     const std::string& channel)
{
    if (_verbose) {
        printf("%.3f Channel %-20s size %d\n", rbuf->recv_utime / 1000000.0,
               channel.data(), rbuf->data_size);
    }

    _lcmOut.publish(channel, rbuf->data, rbuf->data_size);
}

}

}

}

void usage (char* cmd)
{
    fprintf (stderr, "\
Usage: %s [OPTION...] FILE\n\
  Reads packets from an LCM log file and publishes them to LCM.\n\
\n\
Options:\n\
  -v, --verbose       Print information about each packet.\n\
  -s, --speed=NUM     Playback speed multiplier.  Default is 1.0.\n\
  -c, --channel=CHAN  Regular expression of channels to play.\n\
  -l, --lcm-url=URL   Play logged messages on the specified LCM URL.\n\
  -h, --help          Shows some help text and exits.\n\
  \n", cmd);
}


int main(int argc, char ** argv)
{
    struct option longOptions[] = {
        { "help", no_argument, 0, 'h' },
        { "speed", required_argument, 0, 's' },
        { "lcm-url", required_argument, 0, 'l' },
        { "verbose", no_argument, 0, 'v' },
        { "channel", required_argument, 0, 'c' },
        { 0, 0, 0, 0 }
    };

    int c;
    double speed = 1.0;
    std::string channel = ".*";
    std::string lcmUrlOut;
    std::string lcmUrlIn;
    int verbose = 0;
    while ((c = getopt_long (argc, argv, "hp:s:vc:l:", longOptions, 0)) >= 0) {
        switch (c) {
            case 's':
                speed = strtod (optarg, nullptr);
                break;
            case 'l':
                lcmUrlOut = optarg;
                break;
            case 'v':
                verbose = 1;
                break;
            case 'c':
                channel = optarg;
                break;
            case 'h':
            default:
                usage(argv[0]);
                return 1;
        };
    }

    if (optind != argc - 1) {
        usage(argv[0]);
        return 1;
    }

    printf("Using playback speed %f\n", speed);
    std::stringstream ss;
    ss << "file://" << argv[optind] << "?speed=" << speed;
    lcmUrlIn = ss.str();

    cvm::sensor::logger::Player player(verbose, lcmUrlIn, lcmUrlOut, channel);
    player.loop();

    return 0;
}
