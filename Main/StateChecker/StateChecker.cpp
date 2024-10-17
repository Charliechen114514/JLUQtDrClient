#include "StateChecker.h"
#include "AnalysisPolicyHandler.h"
StateChecker::ErrorCode StateChecker::gain_state_info(
    const QString& from_handling_message) {
    // check the auth first
    // 验证
    if (from_handling_message.contains(
            AnalysisPolicyHandler::PolicyMakerFactory::
                createAuthFailedPolicy())) {
        return ErrorCode::AUTH_FAILED;
    }

    // 实际超时
    if (from_handling_message.contains(
            AnalysisPolicyHandler::PolicyMakerFactory::
                createRealTimeOutPolicy())) {
        return ErrorCode::TIME_OUT;
    }

    // 可能的超时
    if (from_handling_message.contains(
            AnalysisPolicyHandler::PolicyMakerFactory::
                createPossibleTimeOutPolicy())) {
        return ErrorCode::POSSIBLE_TIME_OUT;
    }

    // 等待
    for (const auto& each : AnalysisPolicyHandler::ONLINE_STATE) {
        if (!from_handling_message.contains(each)) {
            return ErrorCode::WAITING;
        }
    }

    // 正在连接
    return ErrorCode::NO_ERROR;
}
