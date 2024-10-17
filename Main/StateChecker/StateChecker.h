#ifndef STATECHECKER_H
#define STATECHECKER_H
#include <QString>
class StateChecker {
public:
    StateChecker() = default;
    enum class ErrorCode {
        NO_ERROR,
        WAITING,
        AUTH_FAILED,
        POSSIBLE_TIME_OUT,
        TIME_OUT
    };

    static ErrorCode gain_state_info(const QString& from_handling_message);
};

#endif  // STATECHECKER_H
