#define DEBUGON
#define FUNC                            __PRETTY_FUNCTION__

/*******************************************************************************
********************************************************************************
**                                                                            **
**                             Serial Debug                                   **
**                                                                            **
**      Class to write debug info to the serial port (USB).                   **
**      Originally written to use String class but converted to a more        **
**      simple char * as the String class causes memory fragmentation.        **
**      Floats don't work with format strings in Arduino libraries so         **
**      there is a special routine for floats.                                **
**                                                                            **
********************************************************************************
*******************************************************************************/

#define MAXDEBUGSTRLEN                  200
#define SERIALBAUDRATE                  115200 // max for serial monitor

class SerialDebug 
{
  public:
    SerialDebug (const char * DebugString);
    void Line (const char * ActivityString, const char * Format = NULL, ...);
    void Line (const char * ActivityString, float FloatData1, 
                                             float FloatData2 = 0.0, 
                                             float FloatData3 = 0.0);
}; /* SerialDebug */

SerialDebug * Debug; 


#ifdef DEBUGON
  #define DEBUG(...) Debug->Line (__VA_ARGS__)
#else
  #define DEBUG(...)
#endif
