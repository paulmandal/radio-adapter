/**
 * Message transformation configuration definitions
 */
 
#ifndef MessageTransformConfigs_h
#define MessageTransformConfigs_h

#include "msg_transform.h"

/**
 * GGA Message Transform
 */
const FieldResize ggaLeftPaddings[] = {
  {7, 2},
  {8, 4},
  {9, 7},
  {11, 6},
  {14, 4}
};

const FieldResize ggaRightShrinks[] = {};

const FieldAddition ggaPrefixes[] = {};

const FieldAddition ggaSuffixes[] = {
  {1, ".000"}
};

const ConstantField ggaConstants[] = {
  {13, "000.0"}
};

const char *ggaMessageEnd = "0000";

MessageTransform ggaTransform(ggaLeftPaddings,
                              (sizeof(ggaLeftPaddings) / sizeof(FieldResize)),
                              ggaRightShrinks,
                              (sizeof(ggaRightShrinks) / sizeof(FieldResize)),
                              ggaPrefixes,
                              (sizeof(ggaPrefixes) / sizeof(FieldAddition)),
                              ggaSuffixes,
                              (sizeof(ggaSuffixes) / sizeof(FieldAddition)),
                              ggaConstants,
                              (sizeof(ggaConstants) / sizeof(ConstantField)),
                              ggaMessageEnd);

/**
 * GLL Message Transform
 */
const FieldResize gllLeftPaddings[] = {};

const FieldResize gllRightShrinks[] = {
  {3, 9}
};

const FieldAddition gllPrefixes[] = {};

const FieldAddition gllSuffixes[] = {
  {5, ".000"}
};

const ConstantField gllConstants[] = {};

const char *gllMessageEnd = "";

MessageTransform gllTransform(gllLeftPaddings,
                              (sizeof(gllLeftPaddings) / sizeof(FieldResize)),
                              gllRightShrinks,
                              (sizeof(gllRightShrinks) / sizeof(FieldResize)),
                              gllPrefixes,
                              (sizeof(gllPrefixes) / sizeof(FieldAddition)),
                              gllSuffixes,
                              (sizeof(gllSuffixes) / sizeof(FieldAddition)),
                              gllConstants,
                              (sizeof(gllConstants) / sizeof(ConstantField)),
                              gllMessageEnd);

/**
 * RMC Message Transform
 */
const FieldResize rmcLeftPaddings[] = {};

const FieldResize rmcRightShrinks[] = {};

const FieldAddition rmcPrefixes[] = {};

const FieldAddition rmcSuffixes[] = {};

const ConstantField rmcConstants[] = {};

const char *rmcMessageEnd = "";

MessageTransform rmcTransform(rmcLeftPaddings,
                              (sizeof(rmcLeftPaddings) / sizeof(FieldResize)),
                              rmcRightShrinks,
                              (sizeof(rmcRightShrinks) / sizeof(FieldResize)),
                              rmcPrefixes,
                              (sizeof(rmcPrefixes) / sizeof(FieldAddition)),
                              rmcSuffixes,
                              (sizeof(rmcSuffixes) / sizeof(FieldAddition)),
                              rmcConstants,
                              (sizeof(rmcConstants) / sizeof(ConstantField)),
                              rmcMessageEnd);

/**
 * VTG Message Transform
 */
const FieldResize vtgLeftPaddings[] = {};

const FieldResize vtgRightShrinks[] = {};

const FieldAddition vtgPrefixes[] = {};

const FieldAddition vtgSuffixes[] = {};

const ConstantField vtgConstants[] = {};

const char *vtgMessageEnd = "";

MessageTransform vtgTransform(vtgLeftPaddings,
                              (sizeof(vtgLeftPaddings) / sizeof(FieldResize)),
                              vtgRightShrinks,
                              (sizeof(vtgRightShrinks) / sizeof(FieldResize)),
                              vtgPrefixes,
                              (sizeof(vtgPrefixes) / sizeof(FieldAddition)),
                              vtgSuffixes,
                              (sizeof(vtgSuffixes) / sizeof(FieldAddition)),
                              vtgConstants,
                              (sizeof(vtgConstants) / sizeof(ConstantField)),
                              vtgMessageEnd);

/**
 * GSA Message Transform
 */
const FieldResize gsaLeftPaddings[] = {};

const FieldResize gsaRightShrinks[] = {};

const FieldAddition gsaPrefixes[] = {};

const FieldAddition gsaSuffixes[] = {};

const ConstantField gsaConstants[] = {};

const char *gsaMessageEnd = "";

MessageTransform gsaTransform(gsaLeftPaddings,
                              (sizeof(gsaLeftPaddings) / sizeof(FieldResize)),
                              gsaRightShrinks,
                              (sizeof(gsaRightShrinks) / sizeof(FieldResize)),
                              gsaPrefixes,
                              (sizeof(gsaPrefixes) / sizeof(FieldAddition)),
                              gsaSuffixes,
                              (sizeof(gsaSuffixes) / sizeof(FieldAddition)),
                              gsaConstants,
                              (sizeof(gsaConstants) / sizeof(ConstantField)),
                              gsaMessageEnd);

/**
 * GSV Message Transform
 */
const FieldResize gsvLeftPaddings[] = {};

const FieldResize gsvRightShrinks[] = {};

const FieldAddition gsvPrefixes[] = {};

const FieldAddition gsvSuffixes[] = {};

const ConstantField gsvConstants[] = {};

const char *gsvMessageEnd = "";

MessageTransform gsvTransform(gsvLeftPaddings,
                              (sizeof(gsvLeftPaddings) / sizeof(FieldResize)),
                              gsvRightShrinks,
                              (sizeof(gsvRightShrinks) / sizeof(FieldResize)),
                              gsvPrefixes,
                              (sizeof(gsvPrefixes) / sizeof(FieldAddition)),
                              gsvSuffixes,
                              (sizeof(gsvSuffixes) / sizeof(FieldAddition)),
                              gsvConstants,
                              (sizeof(gsvConstants) / sizeof(ConstantField)),
                              gsvMessageEnd);

/**
 * ZDA Message Transform
 */
const FieldResize zdaLeftPaddings[] = {};

const FieldResize zdaRightShrinks[] = {};

const FieldAddition zdaPrefixes[] = {};

const FieldAddition zdaSuffixes[] = {};

const ConstantField zdaConstants[] = {};

const char *zdaMessageEnd = "";

MessageTransform zdaTransform(zdaLeftPaddings,
                              (sizeof(zdaLeftPaddings) / sizeof(FieldResize)),
                              zdaRightShrinks,
                              (sizeof(zdaRightShrinks) / sizeof(FieldResize)),
                              zdaPrefixes,
                              (sizeof(zdaPrefixes) / sizeof(FieldAddition)),
                              zdaSuffixes,
                              (sizeof(zdaSuffixes) / sizeof(FieldAddition)),
                              zdaConstants,
                              (sizeof(zdaConstants) / sizeof(ConstantField)),
                              zdaMessageEnd);


struct TransformMapping {
  const char *nmeaMessageType;
  MessageTransform &transformer;
};

extern const TransformMapping transformMap[] = {
  {"$GPGGA", ggaTransform},
  {"$GPGLL", gllTransform},
  {"$GPRMC", rmcTransform},
  {"$GPVTG", vtgTransform},
  {"$GPGSA", gsaTransform},
  {"$GPGSV", gsvTransform},
  {"$GPZDA", zdaTransform}
};

#endif
