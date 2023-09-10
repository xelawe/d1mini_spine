/*******************************************************************************
*                                                                              *
*                  SerialDebug::Line (char *, char *, varargs)                 *
*                                                                              *
*******************************************************************************/

void SerialDebug::Line (const char * ActivityString, const char * Format, ...)
{
  char IntDebugStr [MAXDEBUGSTRLEN];
  va_list args;

  // if no format then just write out the activity string
  if ((Format == NULL) || (Format [0] == 0))
  {
    Serial.print (millis()); Serial.print (" ");
    Serial.println (ActivityString);
    return;
  }

  // create the debug string
  va_start (args, Format);
  vsnprintf (IntDebugStr, MAXDEBUGSTRLEN, Format, args);
  IntDebugStr [sizeof (IntDebugStr) - 1] = 0;
  va_end (args);
  
  // write out the debug string
  va_start (args, Format);
  Serial.print (millis()); Serial.print (" ");
  Serial.print (ActivityString); Serial.print (": ");
  Serial.println (IntDebugStr);  
  va_end (args);
  
} /* SerialDebug::Line (char *, char *, ...) */



/*******************************************************************************
*                                                                              *
*                SerialDebug::Line (char *, float, float, float)               *
*                                                                              *
*******************************************************************************/

void SerialDebug::Line (const char * ActivityString, float FloatData1, 
                                            float FloatData2, float FloatData3)
{
  char IntDebugStr [MAXDEBUGSTRLEN];
  char IntDebugStr1 [MAXDEBUGSTRLEN];
  char IntDebugStr2 [MAXDEBUGSTRLEN];
  char IntDebugStr3 [MAXDEBUGSTRLEN];

  // create the debug string - sprintf of float fails - dtostrf workaround
  dtostrf (FloatData1, 11, 5, IntDebugStr1);
  dtostrf (FloatData2, 11, 5, IntDebugStr2);
  dtostrf (FloatData3, 11, 5, IntDebugStr3);
  snprintf (IntDebugStr, MAXDEBUGSTRLEN, "%s: %s %s %s", ActivityString, 
               trim (IntDebugStr1), trim (IntDebugStr2), trim (IntDebugStr3));
  
  // write out the debug string
  Serial.print (millis()); Serial.print (" ");
  Serial.println(IntDebugStr);  

} /* SerialDebug::Line (char *, float, float, float) */



/*******************************************************************************
*                                                                              *
*                          SerialDebug::SerialDebug                            *
*                                                                              *
*       SerialDebug debug class constructor- initialise USB serial and         *
*       write a start line.                                                    *
*                                                                              *
*******************************************************************************/

SerialDebug::SerialDebug (const char * DebugString)
{
  // initialize serial communication at 115200 bits per second which is 
  // max for communication with IDE serial monitor
  Serial.begin(SERIALBAUDRATE);

  Line ("");
  Serial.print (millis()); Serial.print (" ");
  Line (DebugString);
  
} /* SerialDebug::SerialDebug */

/*******************************************************************************
*                                                                              *
*                                  trim                                        *
*                                                                              *
*       String whitespace trimming routine; C doesn't have one for char *      *
*       strings for some reason.                                               *
*                                                                              *
*******************************************************************************/

char * trim (char *s) 
{
    char * ptr;

    // return if NULL string
    if (!s) return NULL;    

    // return if empty string
    if (!*s) return s;   
       
    for (ptr = s + strlen (s) - 1; (ptr >= s) && isspace(*ptr); --ptr);
    ptr[1] = '\0';
    for (ptr = s; (*ptr != '\0') && isspace(*ptr); ptr++);
    
    return (ptr);
    
} /* trim */
