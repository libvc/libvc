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
 * $Id: vc.c,v 1.2 2003/05/13 06:09:19 ahsu Exp $
 */


#include "vc.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUF_LEN 80

/*** STRUCTS ***/

struct vc_component_tag
{
  char *group;
  char *name;
  vc_component_param *param;
  char *value;
  vc_component *next;
};

struct vc_component_param_tag
{
  char *name;
  char *value;
  vc_component_param *next;
};

/*** FUNCTION DEFINITIONS ***/

/***************************************************************************
    Returns a new vc_component with everything set to NULL.  The
    user of the new vc_component will be responsible for freeing
    it in the future with a call to vc_delete or vc_delete_deep.
 */

vc_component *
vc_new ()
{
  vc_component *new_vc = NULL;

  new_vc = (vc_component *) malloc (sizeof (vc_component));

  if (NULL == new_vc)
    {
      fprintf (stderr, "unable to malloc a new vc_component\n");
      exit (1);
    }
  else
    {
      new_vc->group = NULL;
      new_vc->name = NULL;
      new_vc->param = NULL;
      new_vc->value = NULL;
      new_vc->next = NULL;
    }

  return new_vc;
}

/***************************************************************************
    Sets the group of a vc_component by making a copy of the
    given group.  Does nothing if the given vc_component is NULL.
    Returns the given vc_component.
 */

vc_component *
vc_set_group (vc_component * vc, const char *group)
{
  if (NULL != vc)
    {
      free (vc->group);
      vc->group = strdup (group);
    }

  return vc;
}

/***************************************************************************
    Sets the name of a vc_component by making a copy of the given
    name.  Does nothing if the given vc_component is NULL.
    Returns the given vc_component.
 */

vc_component *
vc_set_name (vc_component * vc, char *name)
{
  if (NULL != vc)
    {
      free (vc->name);
      vc->name = strdup (name);
    }

  return vc;
}

/***************************************************************************
    Appends to the linked-list of parameters in the given
    vc_component.  Does nothing if the given vc_component is
    NULL.  Returns the given vc_component.
 */

vc_component *
vc_add_param (vc_component * vc, vc_component_param * vc_param)
{
  if (NULL != vc)
    {
      vc_component_param *p = NULL;
      p = vc->param;

      if (NULL == p)
        {
          vc->param = vc_param;
        }
      else
        {
          while (NULL != p->next)
            {
              p = p->next;
            }

          p->next = vc_param;
        }
    }

  return vc;
}

/***************************************************************************
    Sets the value of a vc_component by making a copy of the
    given value.  Does nothing if the given vc_component is NULL.
    Returns the given vc_component.
 */

vc_component *
vc_set_value (vc_component * vc, const char *value)
{
  if (NULL != vc)
    {
      free (vc->value);
      vc->value = strdup (value);
    }

  return vc;
}

/***************************************************************************
    Traverses to the end of the list of head and then appends tail
    as the next node.  If head is null, does nothing.  Returns head.
 */

vc_component *
vc_link (vc_component * head, vc_component * tail)
{
  if (NULL != head)
    {
      vc_component *vc = NULL;
      vc = head;

      while (NULL != vc->next)
        {
          vc = vc->next;
        }

      vc->next = tail;
    }

  return head;
}

/***************************************************************************
    This is a convenience function for appending a new vc_component
    to the end of the list pointed to by the given vc_component.
    Returns a pointer to the newly created vc_component if
    successful, NULL otherwise.
 */

vc_component *
vc_append_with_name (vc_component * vc, char *name)
{
  vc_component *new_vc = NULL;
  if (NULL != vc)
    {
      new_vc = vc_new ();
      vc_set_name (new_vc, name);
      vc_link (vc, new_vc);
    }

  return new_vc;
}

/***************************************************************************
    Checks the parameters of the given vc_component to see if
    there exists a parameter name `TYPE' with a value of `pref'.
    Returns a value of 1 if found, else 0.
 */

int
vc_is_preferred (vc_component * vc)
{
  int ret_val = 0;

  if (NULL != vc)
    {
      vc_component_param *vc_param = NULL;
      char *value = NULL;
      int done = 0;

      for (vc_param = vc_param_get_by_name (vc->param, "TYPE");
           (NULL != vc_param) && (!done);
           vc_param = vc_param_get_next_by_name (vc_param, "TYPE"))
        {
          value = vc_param_get_value (vc_param);

          if (NULL != value)
            {
              if (0 == strcmp (value, "pref"))
                {
                  ret_val = 1;
                  done = 1;
                }
            }
        }
    }

  return ret_val;
}

/***************************************************************************
    Returns the pointer to the name of the preferred telephone
    number of the given vc.  This is done by checking for `TYPE'
    parameters with a value of `pref'.  If no such parameter is
    found, then the first vc_component with the name `TEL' will
    be returned.  Returns NULL if none found.  Users of this function
    must not modify the contents to which the returned pointer
    points to.

    FIXME: lots of duplicate code with vc_get_preferred_email
 */

char *
vc_get_preferred_tel (vc_component * v)
{
  char *tel = NULL;
  int done = 0;
  vc_component *vc = NULL;

  vc = vc_get_next_by_name (v, VC_TELEPHONE);
  tel = vc_get_value (vc);

  if (!vc_is_preferred (vc))
    {
      while ((NULL != vc) && (!done))
        {
          vc = vc_get_next_by_name (vc, VC_TELEPHONE);
          if (vc_is_preferred (vc))
            {
              tel = vc_get_value (vc);
              done = 1;
            }
        }
    }

  return tel;
}

/***************************************************************************
    Returns the pointer to the name of the preferred email number
    of the given vc.  This is done by checking for `TYPE'
    parameters with a value of `pref'.  If no such parameter is
    found, then the first vc_component with the name `EMAIL'
    will be returned.  Returns NULL if none found.  Users of this
    function must not modify the contents to which the returned
    pointer points to.

    FIXME: lots of duplicate code with vc_get_preferred_tel
 */

char *
vc_get_preferred_email (vc_component * v)
{
  char *email = NULL;
  int done = 0;
  vc_component *vc = NULL;

  vc = vc_get_next_by_name (v, VC_EMAIL);
  email = vc_get_value (vc);

  if (!vc_is_preferred (vc))
    {
      while ((NULL != vc) && (!done))
        {
          vc = vc_get_next_by_name (vc, VC_EMAIL);
          if (vc_is_preferred (vc))
            {
              email = vc_get_value (vc);
              done = 1;
            }
        }
    }

  return email;
}

/***************************************************************************
    Returns the pointer to the group of the given vc_component.
    Users of this function must not modify the contents to which
    the pointer points to (use vc_set_group function for modifying
    the group).  Returns NULL if no group found.
 */

char *
vc_get_group (const vc_component * vc)
{
  char *ret_val = NULL;
  if (NULL != vc)
    {
      ret_val = vc->group;
    }

  return ret_val;
}

/***************************************************************************
    Returns the pointer to the name of the given vc_component.
    Users of this function must not modify the contents to which
    the pointer points to (use vc_set_name function for modifying
    the name).  Returns NULL if no name found.
 */

char *
vc_get_name (const vc_component * vc)
{
  char *ret_val = NULL;
  if (NULL != vc)
    {
      ret_val = vc->name;
    }

  return ret_val;
}

/***************************************************************************
    Returns the pointer to the first parameter of the given
    vc_component.  Users of this function may use the modify
    functions for vc_component_param to change the contents of
    the returned parameter.  Returns NULL if no parameter found.
 */

vc_component_param *
vc_get_param (const vc_component * vc)
{
  vc_component_param *ret_val = NULL;
  if (NULL != vc)
    {
      ret_val = vc->param;
    }

  return ret_val;
}

/***************************************************************************
    Returns the pointer to the value of the given vc_component.
    Users of this function must not modify the contents to which
    the pointer points to (use vc_set_value function for modifying
    the value).  Returns NULL if no value found.
 */

char *
vc_get_value (const vc_component * vc)
{
  char *ret_val = NULL;
  if (NULL != vc)
    {
      ret_val = vc->value;
    }

  return ret_val;
}

/***************************************************************************
    Returns a new vc_component_param with everything set to NULL.
    The user of the new vc_component_param will be responsible
    for freeing it in the future with a call to vc_param_delete or
    vc_param_delete_deep.
 */

vc_component_param *
vc_param_new ()
{
  vc_component_param *new_vc_param = NULL;

  new_vc_param = (vc_component_param *) malloc (sizeof (vc_component_param));

  if (NULL == new_vc_param)
    {
      fprintf (stderr, "unable to malloc a new vc_component_param\n");
      exit (1);
    }
  else
    {
      new_vc_param->name = NULL;
      new_vc_param->value = NULL;
      new_vc_param->next = NULL;
    }

  return new_vc_param;
}

/***************************************************************************
    Sets the name of a vc_component_param by making a copy of
    the given name.  Does nothing if the given vc_component_param
    is NULL.  Returns the given vc_component_param.
 */

vc_component_param *
vc_param_set_name (vc_component_param * vc_param, const char *name)
{
  if (NULL != vc_param)
    {
      free (vc_param->name);
      vc_param->name = strdup (name);
    }

  return vc_param;
}

/***************************************************************************
    Sets the value of a vc_component_param by making a copy of
    the given value.  Does nothing if the given vc_component_param
    is NULL.  Returns the given vc_component_param.
 */

vc_component_param *
vc_param_set_value (vc_component_param * vc_param, const char *value)
{
  if (NULL != vc_param)
    {
      free (vc_param->value);
      vc_param->value = strdup (value);
    }

  return vc_param;
}

/***************************************************************************
    Traverses to the end of the list of head and then appends tail
    as the next node.  If head is null, does nothing.  Returns head.
 */

vc_component_param *
vc_param_link (vc_component_param * head, vc_component_param * tail)
{
  if (NULL != head)
    {
      vc_component_param *vc_param = NULL;
      vc_param = head;

      while (NULL != vc_param->next)
        {
          vc_param = vc_param->next;
        }

      vc_param->next = tail;
    }

  return head;
}

/***************************************************************************
    Returns the pointer to the name of the given vc_component_param.
    Users of this function must not modify the contents to which
    the pointer points to (use vc_param_set_name function for
    modifying the name).  Returns NULL if no name found.
 */

char *
vc_param_get_name (const vc_component_param * vc_param)
{
  char *ret_val = NULL;
  if (NULL != vc_param)
    {
      ret_val = vc_param->name;
    }

  return ret_val;
}

/***************************************************************************
    Returns the pointer to the value of the given vc_component_param.
    Users of this function must not modify the contents to which
    the pointer points to (use vc_param_set_value function for
    modifying the value).  Returns NULL if no name found.
 */

char *
vc_param_get_value (const vc_component_param * vc_param)
{
  char *ret_val = NULL;
  if (NULL != vc_param)
    {
      ret_val = vc_param->value;
    }

  return ret_val;
}

/***************************************************************************
    Returns the next vc_component linked to the given one.
    Returns NULL if none left.
 */

vc_component *
vc_get_next (const vc_component * vc)
{
  vc_component *ret_val = NULL;

  if (NULL != vc)
    {
      ret_val = vc->next;
    }

  return ret_val;
}

/***************************************************************************
    Searches for a vc_component that matches the given name,
    starting with the one after the given vc_component.  Returns
    NULL if none is found.
 */

vc_component *
vc_get_next_by_name (vc_component * vc, const char *name)
{
  vc_component *result_vc = NULL;
  vc_component *tmp_vc = NULL;
  int done = 0;

  if ((NULL != name) && (NULL != vc))
    {
      tmp_vc = vc->next;
      while ((0 == done) && (NULL != tmp_vc))
        {
          if (NULL != tmp_vc->name)
            {
              if (0 == strcmp (name, tmp_vc->name))
                {
                  result_vc = tmp_vc;
                  done = 1;
                }
            }
          tmp_vc = tmp_vc->next;
        }
    }

  return result_vc;
}

/***************************************************************************
    Returns the next vc_component_param linked to the given one.
    Returns NULL if none left.
 */

vc_component_param *
vc_param_get_next (const vc_component_param * vc_param)
{
  vc_component_param *ret_val = NULL;

  if (NULL != vc_param)
    {
      ret_val = vc_param->next;
    }

  return ret_val;
}

/***************************************************************************
    Searches for a vc_component_param that matches the given
    name, starting with the given vc_component_param.  Returns
    NULL if none is found.

    FIXME: lots of code duplicated from vc_param_get_next_by_name
 */

vc_component_param *
vc_param_get_by_name (vc_component_param * vc_param, const char *name)
{
  vc_component_param *result_vc_param = NULL;
  vc_component_param *tmp_vc_param = NULL;
  int done = 0;

  if ((NULL != name) && (NULL != vc_param))
    {
      tmp_vc_param = vc_param;
      while ((0 == done) && (NULL != tmp_vc_param))
        {
          if (NULL != tmp_vc_param->name)
            {
              if (0 == strcmp (name, tmp_vc_param->name))
                {
                  result_vc_param = tmp_vc_param;
                  done = 1;
                }
            }
          tmp_vc_param = tmp_vc_param->next;
        }
    }

  return result_vc_param;
}

/***************************************************************************
    Searches for a vc_component_param that matches the given
    name, starting with the one after the given vc_component_param.
    Returns NULL if none is found.

    FIXME: lots of code duplicated from vc_param_get_by_name
 */

vc_component_param *
vc_param_get_next_by_name (vc_component_param * vc_param, const char *name)
{
  vc_component_param *result_vc_param = NULL;
  vc_component_param *tmp_vc_param = NULL;
  int done = 0;

  if ((NULL != name) && (NULL != vc_param))
    {
      tmp_vc_param = vc_param->next;
      while ((0 == done) && (NULL != tmp_vc_param))
        {
          if (NULL != tmp_vc_param->name)
            {
              if (0 == strcmp (name, tmp_vc_param->name))
                {
                  result_vc_param = tmp_vc_param;
                  done = 1;
                }
            }
          tmp_vc_param = tmp_vc_param->next;
        }
    }

  return result_vc_param;
}

/***************************************************************************
    Performs a "shallow" delete of the given vc_component.  This
    means that only the given vc_component will be freed.  As a
    side-effect, a "deep" delete of all the associated parameters
    will be performed.  A responsible user of this function would
    also remember to set the given vc_component pointer variable
    to NULL when this function returns.
 */

void
vc_delete (vc_component * vc)
{
  if (NULL != vc)
    {
      free (vc->group);
      free (vc->name);
      vc_param_delete_deep (vc->param);
      free (vc->value);
      free (vc);
    }
}

/***************************************************************************
    Performs a "deep" delete of the given vc_component.  This
    means that all the vc_components linked to the given one
    will also be deleted.  A responsible user of this function would
    also remember to set the given vc_component pointer variable
    to NULL when this function returns.
 */

void
vc_delete_deep (vc_component * vc)
{
  vc_component *tmp_vc = NULL;
  vc_component *vc_to_free = NULL;

  tmp_vc = vc;
  while (NULL != tmp_vc)
    {
      vc_to_free = tmp_vc;
      tmp_vc = tmp_vc->next;

      vc_delete (vc_to_free);
    }
}

/***************************************************************************
    Performs a "shallow" delete of the given vc_component_param.
    This means that only the given vc_component_param will be
    freed.  A responsible user of this function would also remember
    to set the given vc_component_param pointer variable to NULL
    when this function returns.
 */

void
vc_param_delete (vc_component_param * vc_param)
{
  if (NULL != vc_param)
    {
      free (vc_param->name);
      free (vc_param->value);
      free (vc_param);
    }
}

/***************************************************************************
    Performs a "deep" delete of the given vc_component_param.
    This means that all the vc_component_params linked to the
    given one will also be deleted.  A responsible user of this
    function would also remember to set the given vc_component_param
    pointer variable to NULL when this function returns.
 */

void
vc_param_delete_deep (vc_component_param * vc_param)
{
  vc_component_param *tmp_vc_param = NULL;
  vc_component_param *vc_param_to_free = NULL;

  tmp_vc_param = vc_param;
  while (NULL != tmp_vc_param)
    {
      vc_param_to_free = tmp_vc_param;
      tmp_vc_param = tmp_vc_param->next;

      vc_param_delete (vc_param_to_free);
    }
}

/***************************************************************************
    Prints the linked-list of vc_component_param to the given
    FILE pointer.
 */

void
fprintf_vc_component_param (FILE * fp, vc_component_param * vc_param)
{
  vc_component_param *tmp_vc_param = NULL;

  tmp_vc_param = vc_param;

  for (tmp_vc_param = vc_param; NULL != tmp_vc_param;
       tmp_vc_param = vc_param_get_next (tmp_vc_param))
    {
      fprintf (fp, ";%s=%s", tmp_vc_param->name, tmp_vc_param->value);
    }
}

/***************************************************************************
    Prints a single vc_component to the given FILE pointer.
 */

void
fprintf_vc_component (FILE * fp, vc_component * vc)
{
  if (NULL != vc)
    {
      if (NULL != vc->group)
        {
          fprintf (fp, "%s.", vc->group);
        }

      /* the name is expected to exist */
      fprintf (fp, "%s", vc->name);

      fprintf_vc_component_param (fp, vc->param);
      fprintf (fp, ":");

      if (NULL != vc->value)
        {
          fprintf (fp, "%s", vc->value);
        }

      fprintf (fp, "\n");
    }
}

/***************************************************************************
    Prints the entire vCard to the given FILE pointer.
 */

void
fprintf_vcard (FILE * fp, vc_component * vcard)
{
  vc_component *vc = NULL;

  vc = vcard;
  if (NULL != vc)
    {
      fprintf (fp, "BEGIN:VCARD\n");

      for (vc = vc->next; NULL != vc; vc = vc->next)
        {
          fprintf_vc_component (fp, vc);
        }

      fprintf (fp, "END:VCARD\n");
    }
}

/***************************************************************************
    Returns the number of vCards found in the given FILE pointer.
 */

int
count_vcards (FILE * fp)
{
  char buf[256];
  int counter = 0;

  while (EOF != fscanf (fp, "%s\n", buf))
    {
      if (0 == strcmp (buf, "BEGIN:VCARD"))
        counter++;
    }

  return counter;
}

/***************************************************************************
    Returns a new string of the contents of the section of the given
    string denoted by the part_index.
 */

char *
get_val_struct_part (const char *str, int part_index)
{
  char buf[BUF_LEN];
  int i = 0;
  int j = 0;
  int part_counter = 0;
  int done = 0;
  char *result = NULL;

  if (NULL != str)
    {
      buf[0] = '\0';

      while ('\0' != str[i] && 1 != done)
        {
          if (part_index == part_counter)
            {
              while (str[i] != ';' && i < BUF_LEN - 1)
                {
                  buf[j] = str[i];
                  j++;
                  i++;
                }

              buf[j] = '\0';
              done = 1;
            }
          else
            {
              if (';' == str[i])
                {
                  part_counter++;
                }
              i++;
            }
        }

      if ('\0' != buf[0])
        {
          result = strdup (buf);
        }
    }

  return result;
}
