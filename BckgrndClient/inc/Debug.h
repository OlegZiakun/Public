/*
 * Debug.h
 *
 *      Author: Oleg Ziakun
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <e32svr.h>

#ifdef _UNICODE

#define DEBUG_STRING_LENGTH 255
#define WIDEN2(x) L ## x
#define WIDEN(x) WIDEN2(x)
#define __DBG_FILE__ WIDEN(__FILE__)

#else

#define __DBG_FILE__ __FILE__

#endif//_UNICODE

#ifdef _DEBUG

#define DBG_PRINT_INFO (RDebug::Print(_L("[DEBUG INFO]: %s (line %d)"), __DBG_FILE__, __LINE__ ))
#define DBG_PRINT_SIMPLE_MSG(msg) RDebug::RawPrint(msg)
#define DBG_PRINT_MSG(debugstr,msg) DebugFunc(debugstr, msg)
#define DBG_PRINT_INFO_MSG(debugstr,msg) DebugFunc(debugstr, msg); DBG_PRINT_INFO
#define DBG_PRINT_MSG_INT(debugstr, intmsg) DebugFunc(debugstr, intmsg)
#define DBG_PRINT_INFO_MSG_INT(debugstr, intmsg) DebugFunc(debugstr, intmsg); DBG_PRINT_INFO

inline void DebugFunc(const TDesC& aDebugStr, const TDesC& aMsg)
{
    TBuf< DEBUG_STRING_LENGTH > buffer;
    buffer.Copy(aDebugStr); buffer.Append(_L(": ")); buffer.Append(aMsg);
    DBG_PRINT_SIMPLE_MSG(buffer);
}

inline void DebugFunc(const TDesC& aDebugStr, const TDesC8& aMsg)
{
    TBuf< DEBUG_STRING_LENGTH > buffer,tmpBuffer;
    
    tmpBuffer.Copy(aMsg); buffer.Copy(aDebugStr); buffer.Append(_L(": ")); buffer.Append(tmpBuffer);
    DBG_PRINT_SIMPLE_MSG(buffer);
}

inline void DebugFunc(const TDesC& aDebugStr, TInt aValue)
{
    TBuf< DEBUG_STRING_LENGTH > buffer;
    buffer.Copy(aDebugStr); buffer.Append(_L(": ")); buffer.Append(_L(" <")); buffer.AppendNum(aValue); buffer.Append(_L(">"));  
    DBG_PRINT_SIMPLE_MSG(buffer);
}

#else

#define DBG_PRINT_INFO 
#define DBG_PRINT_SIMPLE_MSG
#define DBG_PRINT_MSG
#define DBG_PRINT_INFO_MSG
#define DBG_PRINT_MSG_INT
#define DBG_PRINT_INFO_MSG_INT

#endif//_DEBUG

#endif /* DEBUG_H_ */
