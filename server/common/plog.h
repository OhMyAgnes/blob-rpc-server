/*******************************************************************************
 * FILENAME:      plog.h
 *
 * AUTHORS:       Shen Qi
 *
 * START DATE:    Thursday April 14th 2022
 *
 * CONTACT:       qi.shen@smartmore.com
 ******************************************************************************/

#ifndef SMARTMORE_SCC_PLOG_H
#define SMARTMORE_SCC_PLOG_H

// conflict with tensor-src/include/tensor/tensor_log.h

#undef LOG_INFO
#undef LOG_DEBUG
#undef LOG_WARN
#undef LOG_ERROR

#include <plog/Log.h>

#undef LOG_INFO
#undef LOG_DEBUG
#undef LOG_WARN
#undef LOG_ERROR

#endif  // SMARTMORE_SCC_PLOG_H