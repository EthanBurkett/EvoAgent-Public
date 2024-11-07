//
// Created by ethan on 9/6/24.
//

#ifndef PAM_H
#define PAM_H

#ifndef SYSCONFDIR
#define SYSCONFDIR "/etc"
#endif

#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <security/pam_ext.h>

/**
 * @brief Drop in replacement for `pam_sm_setcred`
 * @param pamh
 * @param flags
 * @param argc
 * @param argv
 * @return
 */
PAM_EXTERN int EVOPAM_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv);

/**
 * @brief Drop in replacement for `pam_sm_acct_mgmt`
 * @param pamh
 * @param flags
 * @param argc
 * @param argv
 * @return
 */
PAM_EXTERN int EVOPAM_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv);

/**
 * @brief Drop in replacement for `pam_sm_authenticate`
 * @param pamh
 * @param flags
 * @param argc
 * @param argv
 * @return
 */
PAM_EXTERN int EVOPAM_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv);

/**
* @brief Initializes the EVO SDK
* @param {char *} sysconfdir
*/
void EVOPAM_init(const char* sysconfdir);

#endif //PAM_H
