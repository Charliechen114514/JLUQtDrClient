#ifndef ANALYSISPOLICYHANDLER_H
#define ANALYSISPOLICYHANDLER_H
#include <QString>
/*
    For external use of cygnus-logger analysis
*/

#define CONCAT_STATIC(bufferA, bufferB) bufferA##bufferB
#define TIME_OUT_BUFFER
#define TIME_OUT(times) #times
#define TO_STR(buffer)
struct AnalysisPolicyHandler {
    // using in warnings for time out
    static constexpr const char* CONNECTION_MAY_TIME_OUT = "Challenge try: ";
    static constexpr const short try_time_out_times      = 3;
    // real time out
    static constexpr const char* CONNECTION_TIME_OUT =
        "Retrying in 500 milliseconds";

    static constexpr const char* ONLINE_STATE[] = {"Keep alive", "accepted"};

    static constexpr const char* AUTH_FAILED =
        "Authentication failed: Invalid username or password";

    /*
        Interfaces of policy maker
    */

    struct PolicyMakerFactory {
        static QString createPossibleTimeOutPolicy() {
            return CONNECTION_MAY_TIME_OUT +
                   QString::number(try_time_out_times);
        }

        static constexpr const char* createRealTimeOutPolicy() {
            return CONNECTION_TIME_OUT;
        }

        static constexpr const char* createAuthFailedPolicy() {
            return AUTH_FAILED;
        }
    };
};

#endif  // ANALYSISPOLICYHANDLER_H
