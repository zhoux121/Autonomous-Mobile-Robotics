/*
 * @Description: In User Settings Edit
 * @Author: HOU Changhua
 * @Date: 2019-07-10 16:46:17
 * @LastEditTime: 2019-10-15 10:33:45
 * @LastEditors: Please set LastEditors
 */

#include "DeviceDriverSet_xxx0.h"
#include "ApplicationFunctionSet_xxx0.h"

ApplicationFunctionSet Application_FunctionSet;

void setup()
{
  // put your setup code here, to run once:
  Application_FunctionSet.ApplicationFunctionSet_Init();
}

void loop()
{
  //put your main code here, to run repeatedly:
  Application_FunctionSet.ApplicationFunctionSet_SerialPortDataAnalysis();
  Application_FunctionSet.ApplicationFunctionSet_Rocker();
  Application_FunctionSet.CMD_ClearAllFunctionsXXX();
}
