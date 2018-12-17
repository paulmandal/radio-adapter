/**
 * Message transformation configuration definitions
 */
 
#ifndef MessageTransformConfigs_h
#define MessageTransformConfigs_h

#include "msg_transform.h"

/**
 * GGA Message Transform
 */ 
PaddingInfo ggaPaddingInfo[] = 
{
  {7, 2},
  {8, 4},
  {9, 7},
  {11, 6},
  {14, 4}
};

StaticAddition ggaPrefixInfo[] = {};

StaticAddition ggaSuffixInfo[] = 
{
  {1, ".000"}
};

StaticField ggaStaticInfo[] = 
{
  {13, "000.0"}
};

String ggaMessageEnd = "0000";

extern MessageTransform ggaTransform(ggaPaddingInfo, ggaPrefixInfo, ggaSuffixInfo, ggaStaticInfo, ggaMessageEnd);

#endif