/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

/* Copyright 2008, 2009, Mariano Cerdeiro
 *
 * This file is part of OpenSEK.
 *
 * OpenSEK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *             
 * Linking OpenSEK statically or dynamically with other modules is making a
 * combined work based on OpenSEK. Thus, the terms and conditions of the GNU
 * General Public License cover the whole combination.
 *
 * In addition, as a special exception, the copyright holders of OpenSEK give
 * you permission to combine OpenSEK program with free software programs or
 * libraries that are released under the GNU LGPL and with independent modules
 * that communicate with OpenSEK solely through the OpenSEK defined interface. 
 * You may copy and distribute such a system following the terms of the GNU GPL
 * for OpenSEK and the licenses of the other code concerned, provided that you
 * include the source code of that other code when and as the GNU GPL requires
 * distribution of source code.
 *
 * Note that people who make modified versions of OpenSEK are not obligated to
 * grant this special exception for their modified versions; it is their choice
 * whether to do so. The GNU General Public License gives permission to release
 * a modified version without this exception; this exception also makes it
 * possible to release a modified version which carries forward this exception.
 * 
 * OpenSEK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenSEK. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _TS_CFG_H_
#define _TS_CFG_H_
/** \brief Test Suite Configuration Header File
 **
 ** \file TS_Cfg.h
 **/

/** \addtogroup TestSuite
 ** @{ */
/** \addtogroup TestSuite_Global
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe			 Mariano Cerdeiro
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090129 v0.1.1 MaCe add TS_MEMMAP check
 * 20080830 v0.1.0 MaCe	initial version
 */  

/*==================[inclusions]=============================================*/ 

/*==================[macros]=================================================*/
<?php
print "/** \brief TS_MEMMAP definition (DISABLE MemMap is not used, ENABLE MemMap is\n ** used) */\n";
$memmap = $config->getValue("/TESTSUITE/GenConfig","MEMMAP");
switch ($memmap)
{
	case "TRUE":
		print "#define TS_MEMMAP ENABLE\n";
		break;
	default:
		warning("TS_MEMMAP not configured, disabling as default");
	case "FALSE":
		print "#define TS_MEMMAP DISABLE\n";
		break;
}

?>

#define TS_TESTS_COUNT <?php echo $config->getCount("/TESTSUITE","*"); ?>


<?php
$testnames = $config->getList("/TESTSUITE","*");
$count = 0;
foreach ($testnames as $name)
{
   print "#define $name $count\n\n";
	$count++;
}

?>

/*==================[typedef]================================================*/
/** \brief Type definition of TestResult */
typedef unsigned char TS_ResultType;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
#if (TS_MEMMAP == ENABLE)
#define TestSuite_START_SEC_CODE
#include "MemMap.h"
#endif

<?php
$testnames = $config->getList("/TESTSUITE","*");

foreach ($testnames as $name)
{
	$desc = $config->getValue("/TESTSUITE/" . $name,"DESCRIPTION");
	print "/** \brief Test $name\n";
	print " **\n";
	print " ** $desc\n";
	print " **/\n";
	print "TS_ResultType TEST_$name(void)  ATTRIBUTES();\n\n";
}
?>

#if (TS_MEMMAP == ENABLE)
#define TestSuite_STOP_SEC_CODE
#include "MemMap.h"
#endif

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _TS_CFG_H_ */

