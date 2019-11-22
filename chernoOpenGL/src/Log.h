#ifndef LOG_H
#define LOG_H

#if DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#else
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#endif
#include "spdlog/spdlog.h"

#define LOGT(...) SPDLOG_TRACE( __VA_ARGS__ )
#define LOGD(...) SPDLOG_DEBUG( __VA_ARGS__ )
#define LOGI(...) SPDLOG_INFO( __VA_ARGS__ )
#define LOGW(...) SPDLOG_WARN( __VA_ARGS__ )
#define LOGE(...) SPDLOG_ERROR( __VA_ARGS__ )
#define LOGC(...) SPDLOG_CRITICAL( __VA_ARGS__ )

#endif // !LOG_H
