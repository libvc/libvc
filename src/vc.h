/*
 * libvc - vCard library
 * Copyright (C) 2003  Andrew Hsu
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * $Id: vc.h,v 1.1 2003/05/10 09:26:17 ahsu Exp $
 */

#ifndef __VC_H
#define __VC_H 1

#include <stdio.h>

/*** TYPEDEFS ***/

typedef struct vc_component_tag vc_component;
typedef struct vc_component_param_tag vc_component_param;

#ifdef __cplusplus
extern "C"
{
#endif

/*** PROTOTYPES ***/

/* create function for vc_component */
  vc_component *vc_new ();

/* modify functions for vc_component */
  vc_component *vc_set_group (vc_component * vc, const char *group);
  vc_component *vc_set_name (vc_component * vc, char *name);
  vc_component *vc_add_param (vc_component * vc,
                              vc_component_param * vc_param);
  vc_component *vc_set_value (vc_component * vc, const char *value);
  vc_component *vc_link (vc_component * head, vc_component * tail);

/* convenience function */
  vc_component *vc_append_with_name (vc_component * vc, char *name);
  int vc_is_preferred (vc_component * vc);
  char *vc_get_preferred_tel (vc_component * v);
  char *vc_get_preferred_email (vc_component * v);

/* read functions for vc_component */
  char *vc_get_group (const vc_component * vc);
  char *vc_get_name (const vc_component * vc);
  vc_component_param *vc_get_param (const vc_component * vc);
  char *vc_get_value (const vc_component * vc);

/* create function for vc_component_param */
  vc_component_param *vc_param_new ();

/* modify functions for vc_component_param */
  vc_component_param *vc_param_set_name (vc_component_param * vc_param,
                                         const char *name);
  vc_component_param *vc_param_set_value (vc_component_param * vc_param,
                                          const char *value);
  vc_component_param *vc_param_set_str (vc_component_param * vc_param,
                                        const char *str);
  vc_component_param *vc_param_link (vc_component_param * head,
                                     vc_component_param * tail);

/* read functions for vc_component_param */
  char *vc_param_get_name (const vc_component_param * vc_param);
  char *vc_param_get_value (const vc_component_param * vc_param);

/* functions for scrolling through vc_components */
  vc_component *vc_get_next (const vc_component * vc);
  vc_component *vc_get_next_by_name (vc_component * vc, const char *name);

/* functions for scrolling through vc_component_params */
  vc_component_param *vc_param_get_next (const vc_component_param * vc_param);
  vc_component_param *vc_param_get_by_name (vc_component_param
                                            * vc_param, const char *name);
  vc_component_param *vc_param_get_next_by_name (vc_component_param
                                                 * vc_param, const char *name);

/* clean-up functions */
  void vc_delete (vc_component * vc);
  void vc_delete_deep (vc_component * vc);
  void vc_param_delete (vc_component_param * vc_param);
  void vc_param_delete_deep (vc_component_param * vc_param);

/* printing functions */
  void fprintf_vc_component_param (FILE * fp, vc_component_param * vc_param);
  void fprintf_vc_component (FILE * fp, vc_component * vc);
  void fprintf_vcard (FILE * fp, vc_component * vc);

/* parsing functions */
  vc_component *parse_vcard_file (FILE * fp);
  int count_vcards (FILE * fp);
  char *get_val_struct_part (const char *n, int part);

/*** ENUMS ***/

  enum n_parts
  { N_FAMILY, N_GIVEN, N_MIDDLE, N_PREFIX, N_SUFFIX };

  enum adr_parts
  { ADR_PO_BOX, ADR_EXT_ADDRESS, ADR_STREET, ADR_LOCALITY,
    ADR_REGION, ADR_POSTAL_CODE, ADR_COUNTRY
  };

  enum org_parts
  { ORG_NAME, ORG_UNIT_1, ORG_UNIT_2, ORG_UNIT_3, ORG_UNIT_4 };

  enum geo_parts
  { GEO_LATITUDE, GEO_LONGITUDE };

/*** DEFINES ***/

#define VC_ADDRESS              "ADR"
#define VC_AGENT                "AGENT"
#define VC_BIRTHDAY             "BDAY"
#define VC_CATEGORIES           "CATEGORIES"
#define VC_CLASS                "CLASS"
#define VC_DELIVERY_LABEL       "LABEL"
#define VC_EMAIL                "EMAIL"
#define VC_FORMATTED_NAME       "FN"
#define VC_GEOGRAPHIC_POSITION  "GEO"
#define VC_KEY                  "KEY"
#define VC_LOGO                 "LOGO"
#define VC_MAILER               "MAILER"
#define VC_NAME                 "N"
#define VC_NICKNAME             "NICKNAME"
#define VC_NOTE                 "NOTE"
#define VC_ORGANIZATION         "ORG"
#define VC_PHOTO                "PHOTO"
#define VC_PRODUCT_IDENTIFIER   "PRODID"
#define VC_REVISION             "REV"
#define VC_ROLE                 "ROLE"
#define VC_SORT_STRING          "SORT-STRING"
#define VC_SOUND                "SOUND"
#define VC_TELEPHONE            "TEL"
#define VC_TIME_ZONE            "TZ"
#define VC_TITLE                "TITLE"
#define VC_URL                  "URL"
#define VC_VCARD                "VCARD"
#define VC_VERSION              "VERSION"

#ifdef __cplusplus
}
#endif

#endif                          /* __VC_H */
