/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

/**
 * System Test 076
 *
 * Prints out some objects. Tests if print operation properly escapes
 * strings and if newline works.
 *
 * Log
 * ---
 *
 * 2007/01/17   #76: Print will differentiate on strings and print tuples
 * 2007/01/01   #75: First (P.Adelt)
 */

#include "pm.h"
#include "stdio.h"


extern unsigned char usrlib_img[];


int main(void)
{
    #ifdef HAVE_PRINT
    PmReturn_t retval;
    
    retval = pm_init(MEMSPACE_FLASH, usrlib_img);
    PM_RETURN_IF_ERROR(retval);

    retval = pm_run((uint8_t *)"t076");
    pm_reportResult(retval);
    return (int)retval;
    #else
    printf("HAVE_PRINT is not defined. Skipping test.\n");
    return 0;
    #endif /* !HAVE_PRINT */
}
