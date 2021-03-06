/* Guile-Avahi --- Guile bindings for Avahi.
   Copyright (C) 2007, 2008  Ludovic Court�s <ludo@gnu.org>

   This file is part of Guile-Avahi.

   Guile-Avahi is free software; you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation; either version 3 of the License, or (at
   your option) any later version.

   Guile-Avahi is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser
   General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef GUILE_AVAHI_UTILS_H
#define GUILE_AVAHI_UTILS_H

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <libguile.h>


/* Compiler twiddling.  */

#ifdef __GNUC__
# define EXPECT    __builtin_expect
# define NO_RETURN __attribute__ ((__noreturn__))
#else
# define EXPECT(_expr, _value) (_expr)
# define NO_RETURN
#endif

#define EXPECT_TRUE(_expr)  EXPECT ((_expr), 1)
#define EXPECT_FALSE(_expr) EXPECT ((_expr), 0)


/* String handling.  */

/* Store the contents of STRING into a stack-allocated C string.  */
#define SCM_AVAHI_TO_C_STRING(_string, _c_string)			\
do									\
{									\
  size_t _c_len;							\
  _c_len = scm_c_string_length (_string);				\
  (_c_string) = (char *) alloca (_c_len + 1);				\
  (void) scm_to_locale_stringbuf ((_string), (_c_string), _c_len);	\
  (_c_string)[_c_len] = '\0';						\
}									\
while (0)

#define scm_avahi_to_c_string(_string, _c_string, _pos, _func)	\
do								\
{								\
  SCM_VALIDATE_STRING ((_pos), (_string));			\
  SCM_AVAHI_TO_C_STRING ((_string), (_c_string));		\
}								\
while (0)


/* Handling invalid (i.e., already freed) Avahi objects.  */

#define SCM_AVAHI_C_ASSERT_VALID(c_obj)				\
  if (EXPECT_FALSE (c_obj == NULL))				\
    scm_avahi_error (AVAHI_ERR_INVALID_OBJECT, FUNC_NAME);



/* Avahi helpers.  */

#include <avahi-common/watch.h>
#include <avahi-client/client.h>

SCM_API SCM scm_from_avahi_watch_events (AvahiWatchEvent events);
SCM_API SCM scm_from_avahi_interface_index (AvahiIfIndex iface);
SCM_API SCM scm_from_avahi_lookup_result_flags (AvahiLookupResultFlags flags);
SCM_API SCM scm_from_avahi_address (const AvahiAddress *address);
SCM_API SCM scm_from_avahi_string_list (const AvahiStringList *lst);

SCM_API AvahiWatchEvent scm_to_avahi_watch_events (SCM events, int pos,
						   const char *func_name);
SCM_API AvahiClientFlags scm_to_avahi_client_flags (SCM flags, int pos,
						    const char *func_name);
SCM_API AvahiPublishFlags scm_to_avahi_publish_flags (SCM flags, int pos,
						      const char *func_name);
SCM_API AvahiLookupFlags scm_to_avahi_lookup_flags (SCM flags, int pos,
						    const char *func_name);
SCM_API void scm_to_avahi_address (SCM address_protocol, SCM address,
				   AvahiAddress *c_address,
				   int pos, const char *func_name);
SCM_API AvahiIfIndex scm_to_avahi_interface_index (SCM interface, int pos,
						   const char *func_name);

#endif

/* arch-tag: 2cd14488-a545-43e4-8991-7c25b048fd72
 */
