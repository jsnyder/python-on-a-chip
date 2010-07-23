#include "dataXfer.h"
#include <string.h>
#include <stdio.h>

/** \file
 *  \brief Implementation of the \ref index "uC data transfer protocol".
 */

void initDataXfer() {
  resetReceiveMachine();
  clearReceiveStruct();
}


/// \name Send functions
//@{

void xferOutChar(char c) {
  // If we're sending a character that needs escaping, then escape it.
  OUT_CHAR(c);
  if (c == CMD_TOKEN)
    OUT_CHAR(ESCAPED_CMD);
}

void specifyVar(uint u_varIndex, void* pv_data, uint u_size, 
                BOOL b_isWriteable, char* psz_format, char* psz_name,
                char* psz_desc) {
  uint u_len;

  // Make sure this variable exists
  ASSERTM("specifyVar:indexTooHigh", u_varIndex < NUM_XFER_VARS);
  // Make sure the data isn't NULL
  ASSERTM("specifyVar:nullData", pv_data != NULL);
  // Make sure the size is valid
  ASSERTM("specifyVar:invalidSize", (u_size > 0) && (u_size <= 256));

  // Update data structure
  xferVar[u_varIndex].pu8_data = (uint8*) pv_data;
  xferVar[u_varIndex].u8_size = u_size - 1;
  assignBit(u_varIndex, b_isWriteable);

  // Send a command
  OUT_CHAR(CMD_TOKEN);

  // Send a specification: The spec code, index, then length
  xferOutChar(b_isWriteable ? CMD_SEND_RECEIVE_VAR : CMD_SEND_ONLY);
  xferOutChar(u_varIndex);
  // Include the space taken by the three NULL characters, minus one since a
  // length of 1 is sent as 0, plus one for the variable size byte.
  u_len = strlen(psz_format) + strlen(psz_name) + strlen(psz_desc) + 3 - 1 + 1;
  // Allow a maximum string length of 255.
  xferOutChar(u_len <= 255 ? u_len : 255);

  // Send the size of this variable, minus 1 since a size of 1 is sent as a 0.
  xferOutChar(u_size - 1);

  // Send the strings
  u_len = 1;
  do {
    if (u_len++ > 256) return;
    xferOutChar(*psz_format);
  } while (*psz_format++);
  do {
    if (u_len++ > 256) return;
    xferOutChar(*psz_name);
  } while (*psz_name++);
  do {
    if (u_len++ > 256) return;
    xferOutChar(*psz_desc);
  } while (*psz_desc++);
}

void sendVar(uint u_varIndex) {
  XFER_VAR* pXferVar;
  uint8 u8_size;
  uint8* pu8_data;
  // Make sure this variable exists
  ASSERTM("sendVar:indexTooHigh", u_varIndex < NUM_XFER_VARS);
  // Note: The MS C compiler flags the statement
  // XFER_VAR* pXferVar = xferVar + u_varIndex;
  // as an error. It's OK in MS C++. Apparently, the C compiler doesn't
  // support the newer C99 syntax. Therefore, u8_size and pu8_data are
  // also declared above.
  pXferVar = xferVar + u_varIndex;
  ASSERTM("sendVar:indexNotSpecified", pXferVar->pu8_data != NULL);
  // Make sure it's read/write (PC only)
#ifndef __PIC__
  ASSERTM("sendVar:notWriteable", isVarWriteable(u_varIndex));
#endif

  // Send a command
  OUT_CHAR(CMD_TOKEN);

  // Send short/long var info
  u8_size = pXferVar->u8_size;
  if ((u8_size + 1) > SHORT_VAR_MAX_LEN) {
    // Send a long var: The long var code, index, then length
    xferOutChar(CMD_LONG_VAR);
    xferOutChar(u_varIndex);
    xferOutChar(u8_size);
  } else {
    // Send a short var
    xferOutChar((u_varIndex << VAR_SIZE_BITS) | u8_size);
  }

  // Send data
  pu8_data = pXferVar->pu8_data;
  do {
    xferOutChar(*pu8_data++);
  } while (u8_size--);
}

//@}

#ifndef __PIC__
int formatVar(uint u_varIndex, char* psz_buf) {
  XFER_VAR* pXferVar;
  uint8 u8_size;
  unsigned long long ull_buf = 0;  // The biggest data type available

  // Make sure this variable exists
  ASSERTM("formatVar:indexTooHigh", u_varIndex < NUM_XFER_VARS);
  // Note: The MS C compiler flags the statement
  // XFER_VAR* pXferVar = xferVar + u_varIndex;
  // as an error. It's OK in MS C++. Apparently, the C compiler doesn't
  // support the newer C99 syntax. Therefore, u8_size and pu8_data are
  // also declared above.
  pXferVar = xferVar + u_varIndex;
  ASSERTM("formatVar:indexNotSpecified", pXferVar->pu8_data != NULL);
  u8_size = pXferVar->u8_size + 1;

  // Copy the data over to the largest available var for formatting
  ASSERT(u8_size <= sizeof(ull_buf));
  memcpy(&ull_buf, pXferVar->pu8_data, u8_size);
  return sprintf(psz_buf, pXferVar->psz_format, ull_buf);
}
#endif

#ifdef __PIC__
uint receiveVar(char* c) {
    uint u_index;

  // Receive the data by stepping the machine until it outputs
  // something
  do {
    // While there's no data, run the timeout counter
    RECEIVE_ERROR re;
    char c;
    uint32 u32_count = 0;
    while (!isCharReady()) {
      if (u32_count < RECEIVE_TIMEOUT)
        u32_count++;
      doHeartbeat();
    }

    // Step the machine
    c = inChar();
    re = stepReceiveMachine(c, u32_count >= RECEIVE_TIMEOUT);
    if (re != ERR_NONE) {
      outString("Data receive error: ");
      outString(getReceiveErrorString());
      outChar('\n');
    }
  } while (!isReceiveMachineChar(c) && !isReceiveMachineData(&u_index));

  return getReceiveMachineIndex();
}

char inCharXfer() {
  char c;
  while (receiveVar(&c) != CHAR_RECEIVED_INDEX);
  return c;
}
#endif
