/*
 * Copyright (C) 2018 - 2020, Stephan Mueller <smueller@chronox.de>
 *
 * License: see LICENSE file in root directory
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ALL OF
 * WHICH ARE HEREBY DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF NOT ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

#ifndef DEFINITION_H
#define DEFINITION_H

#include <limits.h>
#include <stdint.h>

#include <json-c/json.h>

#include "acvpproxy.h"
#include "atomic.h"
#include "constructor.h"
#include "definition_cipher_drbg.h"
#include "definition_cipher_hash.h"
#include "definition_cipher_mac.h"
#include "definition_cipher_sym.h"
#include "definition_cipher_rsa.h"
#include "definition_cipher_ecdsa.h"
#include "definition_cipher_eddsa.h"
#include "definition_cipher_dsa.h"
#include "definition_cipher_kas_ecc.h"
#include "definition_cipher_kas_ffc.h"
#include "definition_cipher_kdf_ssh.h"
#include "definition_cipher_kdf_ikev1.h"
#include "definition_cipher_kdf_ikev2.h"
#include "definition_cipher_kdf_tls.h"
#include "definition_cipher_kdf_108.h"
#include "definition_cipher_pbkdf.h"
#include "definition_cipher_kas_ifc.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* Operational environment type */
enum def_mod_type {
	MOD_TYPE_SOFTWARE,
	MOD_TYPE_HARDWARE,
	MOD_TYPE_FIRMWARE,
};

/**
 * @brief This data structure defines a particular cipher algorithm
 *	  definition.
 *
 * @var type Specify the cipher type.
 * @var algo Fill in the data structure corresponding to the @param type
 *	       selection.
 */
struct def_algo {
	enum def_algo_type {
		/** symmetric ciphers, incl. AEAD */
		DEF_ALG_TYPE_SYM,
		/** SHA hashes */
		DEF_ALG_TYPE_SHA,
		/** SHAKE cipher */
		DEF_ALG_TYPE_SHAKE,
		/** HMAC ciphers */
		DEF_ALG_TYPE_HMAC,
		/** CMAC ciphers */
		DEF_ALG_TYPE_CMAC,
		/** SP800-90A DRBG cipher */
		DEF_ALG_TYPE_DRBG,
		/** FIPS 186-4 RSA cipher */
		DEF_ALG_TYPE_RSA,
		/** FIPS 186-4 ECDSA cipher */
		DEF_ALG_TYPE_ECDSA,
		/** Bernstein EDDSA cipher */
		DEF_ALG_TYPE_EDDSA,
		/** FIPS 186-4 DSA cipher */
		DEF_ALG_TYPE_DSA,
		/** KAS_ECC (ECDH, ECMQV) cipher */
		DEF_ALG_TYPE_KAS_ECC,
		/** KAS_ECC (Finite Field DH, Finite Field MQV) cipher */
		DEF_ALG_TYPE_KAS_FFC,
		/** SP800-135 KDF: SSH */
		DEF_ALG_TYPE_KDF_SSH,
		/** SP800-135 KDF: IKE v1 */
		DEF_ALG_TYPE_KDF_IKEV1,
		/** SP800-135 KDF: IKE v2 */
		DEF_ALG_TYPE_KDF_IKEV2,
		/** SP800-135 KDF: TLS */
		DEF_ALG_TYPE_KDF_TLS,
		/** SP800-108 KDF */
		DEF_ALG_TYPE_KDF_108,
		/** SP800-132 PBKDF */
		DEF_ALG_TYPE_PBKDF,
	} type;
	union {
		/** DEF_ALG_TYPE_SYM */
		struct def_algo_sym sym;
		/** DEF_ALG_TYPE_SHA */
		struct def_algo_sha sha;
		/** DEF_ALG_TYPE_SHAKE */
		struct def_algo_shake shake;
		/** DEF_ALG_TYPE_HMAC */
		struct def_algo_hmac hmac;
		/** DEF_ALG_TYPE_CMAC */
		struct def_algo_cmac cmac;
		/** DEF_ALG_TYPE_DRBG */
		struct def_algo_drbg drbg;
		/** DEF_ALG_TYPE_RSA */
		struct def_algo_rsa rsa;
		/** DEF_ALG_TYPE_ECDSA */
		struct def_algo_ecdsa ecdsa;
		/** DEF_ALG_TYPE_EDDSA */
		struct def_algo_eddsa eddsa;
		/** DEF_ALG_TYPE_DSA */
		struct def_algo_dsa dsa;
		/** DEF_ALG_TYPE_KAS_ECC */
		struct def_algo_kas_ecc kas_ecc;
		/** DEF_ALG_TYPE_KAS_FFC */
		struct def_algo_kas_ffc kas_ffc;
		/** DEF_ALG_TYPE_KDF_SSH */
		struct def_algo_kdf_ssh kdf_ssh;
		/** DEF_ALG_TYPE_KDF_IKEV1 */
		struct def_algo_kdf_ikev1 kdf_ikev1;
		/** DEF_ALG_TYPE_KDF_IKEV2 */
		struct def_algo_kdf_ikev2 kdf_ikev2;
		/** DEF_ALG_TYPE_KDF_TLS */
		struct def_algo_kdf_tls kdf_tls;
		/** DEF_ALG_TYPE_KDF_108 */
		struct def_algo_kdf_108 kdf_108;
		/** DEF_ALG_TYPE_PBKDF */
		struct def_algo_pbkdf pbkdf;
	} algo;
};

struct def_algo_map {
	const struct def_algo *algos;
	unsigned int num_algos;
	const char *algo_name;
	const char *processor;
	const char *impl_name;
	struct def_algo_map *next;
};

/* Warning, we operate with a signed int, so leave the highest bit untouched */
#define ACVP_REQUEST_INITIAL	(1<<30)
#define ACVP_REQUEST_PROCESSING	(1<<29)
#define ACVP_REQUEST_REJECTED	(1<<28)
#define ACVP_REQUEST_MASK	(ACVP_REQUEST_INITIAL |			\
				 ACVP_REQUEST_PROCESSING |		\
				 ACVP_REQUEST_REJECTED)

static inline uint32_t acvp_id(uint32_t id)
{
	return (id &~ (uint32_t)ACVP_REQUEST_MASK);
}

static inline bool acvp_valid_id(uint32_t id)
{
	if (id == 0 || id & ACVP_REQUEST_MASK)
		return false;
	return true;
}

static inline bool acvp_request_id(uint32_t id)
{
	if (id & ACVP_REQUEST_MASK)
		return true;
	return false;
}

struct def_lock {
	mutex_t lock;
	atomic_t refcnt;
};

/**
 * @brief This data structure defines identifiers of the cipher implementation.
 *	  Note, this information will be posted at the CAVS web site.
 *
 * @var module_name Specify the name of the cryptographic module (i.e. cipher
 *		    implementation) under test.
 * @var module_name_filesafe Same information as @var module_name except
 *			     that the string is cleared of characters
 *			     inappropriate for file names.
 * @var module_name_internal If this is set, this name is used to map to
 *			     uninstantiated definitions. This name is not
 *			     used for external reference.
 * @var module_type Specify the type of the module.
 * @var module_version Specify a string representing the version of the module.
 * @var module_version_filesafe Same information as @var module_version
 *				except that the string is cleared of
 *				characters inappropriate for file names.
 * @var module_description Provide a brief description of the module.
 * @var def_module_file Configuration file holding the information
 * @var acvp_vendor_id Identifier assigned by the ACVP server to vendor
 *		       information.
 * @var acvp_person_id Identifier assigned by the ACVP server to person /
 *		       contact information.
 * @var acvp_addr_id Identifier assigned by the ACVP server to address
 *		     information.
 * @var acvp_module_id Identifier assigned by the ACVP server to module
 *		       information.
 */
struct def_info {
	char *module_name;
	char *module_name_filesafe;
	char *module_name_internal;
	enum def_mod_type module_type;
	char *module_version;
	char *module_version_filesafe;
	char *module_description;

	char *def_module_file;
	uint32_t acvp_vendor_id;
	uint32_t acvp_person_id;
	uint32_t acvp_addr_id;
	uint32_t acvp_module_id;

	struct def_lock *def_lock;
};

/**
 * @brief This data structure contains the required details about the vendor
 *	  of the cipher implementation. Note, this information will be posted
 *	  at the CAVS web site.
 *
 * @var vendor_name Specify the name of the vendor.
 * @var vendor_name_filesafe Same information as @var vendor_name except
 *			     that the string is cleared of characters
 *			     inappropriate for file names.
 * @var vendor_url Specify the homepage of the vendor.
 * @var acvp_vendor_id Identifier assigned by the ACVP server to vendor
 *		       information.
 *
 * @var contact_name Specify the contact person responsible for the CAVS
 *		     test request.
 * @var contact_email Specify the contact email of the person responsible for
 *		      the CAVS test request.
 * @var contact_phone Specify the contact telephone number
 * @var acvp_person_id Identifier assigned by the ACVP server to person /
 *		       contact information.
 *
 * @var addr_street Address: Street
 * @var addr_locality Address: City
 * @var addr_region Address: State
 * @var addr_country: Address Country
 * @var addr_zipcode: Address: Zip code
 * @var acvp_addr_id Identifier assigned by the ACVP server to address
 *		     information.
 *
 * @var def_vendor_file Configuration file holding the information
 */
struct def_vendor {
	char *vendor_name;
	char *vendor_name_filesafe;
	char *vendor_url;
	uint32_t acvp_vendor_id;

	char *contact_name;
	char *contact_email;
	char *contact_phone;
	uint32_t acvp_person_id;

	char *addr_street;
	char *addr_locality;
	char *addr_region;
	char *addr_country;
	char *addr_zipcode;
	uint32_t acvp_addr_id;

	char *def_vendor_file;

	struct def_lock *def_lock;
};

/**
 * @brief Specify operational environment information of the hosting execution
 *	 environment where the module is tested
 *
 * @var env_type Environment type
 * @var oe_env_name Name of the execution environment (e.g. operating
 *		    system or SoC)
 * @var cpe UNKNOWN
 *
 * @var manufacturer Processor manufacturer (e.g. "Intel")
 * @var proc_family Processor family (e.g. "X86")
 * @var proc_family_internal Processor family used for internal definition
 *	resolving
 * @var proc_name Processor name (e.g. "Intel(R) Core(TM) i7-5557U")
 * @var proc_series Processor series (e.g. "Broadwell")
 * @var features Specify features of the CPU that are used by the module
 * @var def_oe_file Configuration file holding the information
 * @var acvp_oe_id Identifier assigned by the ACVP server to OE information.
 * @var acvp_oe_dep_sw_id Identifier assigned by the ACVP server to software
 *			  dependency information, if there is any.
 * @var acvp_oe_dep_proc_id Identifier assigned by the ACVP server to
 *			    processor dependency information, if there is any.
 */
/* Operational environment processor features */
#define OE_PROC_X86_RDRAND	(1<<0)
#define OE_PROC_X86_AESNI	(1<<1)
#define OE_PROC_X86_CLMULNI	(1<<2)
#define OE_PROC_S390_CPACF	(1<<3)
#define OE_PROC_ARM_AES		(1<<4)
struct def_oe {
	enum def_mod_type env_type;
	char *oe_env_name;
	char *cpe;
	char *swid;
	char *oe_description;

	char *manufacturer;
	char *proc_family;
	char *proc_family_internal;
	char *proc_name;
	char *proc_series;
	uint64_t features;

	char *def_oe_file;
	uint32_t acvp_oe_id;
	uint32_t acvp_oe_dep_sw_id;
	uint32_t acvp_oe_dep_proc_id;

	struct def_lock *def_lock;
};

static const struct acvp_feature {
	uint64_t feature;
	const char *name;
} acvp_features[] = {
	{ OE_PROC_X86_RDRAND,	"rdrand" },
	{ OE_PROC_X86_AESNI,	"aes-ni" },
	{ OE_PROC_X86_CLMULNI,	"clmulni" },
	{ OE_PROC_S390_CPACF,	"cpacf" },
	{ OE_PROC_ARM_AES,	"aes" },
};

/**
 * @brief Data structure to for registering out-of-tree module implementation
 *	  definitions. This structure should only be used with the
 *	  ACVP_EXTENSION macro.
 */
struct acvp_extension {
	struct def_algo_map *curr_map;
	unsigned int nrmaps;
};

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define SET_IMPLEMENTATION(impl)					\
	.algos = impl, .num_algos = ARRAY_SIZE(impl)

#define ACVP_EXTENSION(map)						\
	__attribute__ ((visibility ("default")))			\
	struct acvp_extension acvp_extension = { map, ARRAY_SIZE(map) };

/**
 * @brief This data structure is the root of a cipher definition. It is made
 *	 known to the library using the acvp_req_register_def function call
 *	 which should be invoked during the initialization time of the
 *	 library.
 *
 * @var info This pointer provides generic information about the module.
 * @var algos This pointer refers to the cipher specific information. It is
 *	      permissible to register multiple algorithm specifications with
 *	      multiple instances of the data structure. However, all instances
 *	      of the data structure must be adjacent in memory to allow
 *	      iterating over it.
 * @var num_algos The number of algorithm definitions is specified here.
 *		  Commonly ARRAY_SIZE(algos) would be used here.
 * @var uninstantiated_def Reference to uninstantiated algorithm definition
 * @var next This pointer is internal to the library and MUST NOT be used.
 */
struct definition {
	struct def_info *info;
	const struct def_algo *algos;
	unsigned int num_algos;
	struct def_vendor *vendor;
	struct def_oe *oe;
	struct def_algo_map *uninstantiated_def;
	struct definition *next;
};

/**
 * @brief Register uninstantiated algorithm definitions (i.e. definitions
 *	  without meta data of module information, operational environment,
 *	  and vendor information).
 *
 * @param curr_map Pointer to the uninstantiated algorithm definition.
 * @param nrmaps Number of map definitions pointed to by curr_map
 */
void acvp_register_algo_map(struct def_algo_map *curr_map, unsigned int nrmaps);

/**
 * @brief Iterate over all definitions and return when one match is found.
 *	  The processed_ptr can be used to indicate the entry in the linked list
 *	  that is used as a start point but what was already processed. I.e. the
 *	  search will continue with the entry following the processed_ptr.
 *
 *	  If processed_ptr is NULL, the head of the list is used.
 *
 * @param search Search definition
 * @param processed_ptr Starting point in linked list
 *
 * @return Found definition or NULL if no entry found.
 */
struct definition *acvp_find_def(const struct acvp_search_ctx *search,
				 struct definition *processed_ptr);

struct acvp_testid_ctx;
/**
 * @brief Apply the definition database search criteria found in the provided
 *	  JSON object to find the corresponding cipher definition. Match the
 *	  found cipher definition with the one registered in testid_ctx.
 *
 *	  NOTE: Only the first matching definition is checked, since this
 *	  function expects the search criteria to be specific enough to refer
 *	  to only one definition.
 *
 * @param testid_ctx [in] TestID context whose definition that shall be
 *			  obtained.
 * @param def_config [in] JSON object holding the search criteria
 *
 * @return: 0 on success, < 0 on errors
 */
int acvp_match_def(const struct acvp_testid_ctx *testid_ctx,
		   struct json_object *def_config);

/**
 * @brief Convert the provided definition into an unambiguous search criteria
 *	  catalog that can readily be stored.
 *
 * @param testid_ctx [in] TestID context holding the definition that shall
 *			  be unambiguously found again.
 */
int acvp_export_def_search(const struct acvp_testid_ctx *testid_ctx);

/**
 * @brief Convert module name and implementation name into new string
 *	  to uniquely identify module.
 *
 * @newname [out] Newly allocated buffer with new name (caller must free)
 *		  buffer.
 * @module_name [in] Existing module name
 * @impl_name [in] Implementation name of module
 */
int acvp_def_module_name(char **newname, const char *module_name,
			 const char *impl_name);

/**
 * @brief Update the vendor / OE / module ID in the configuration files
 *
 * The *_get_* functions obtain the current IDs and lock the respective
 * context. The *_put_* functions write the IDs to disk and unlock the
 * context.
 *
 * @return: 0 on success, < 0 on error (when the *_get_* functions return an
 *	    error, the lock is not taken).
 */
int acvp_def_get_vendor_id(struct def_vendor *def_vendor);
int acvp_def_put_vendor_id(struct def_vendor *def_vendor);

int acvp_def_get_person_id(struct def_vendor *def_vendor);
int acvp_def_put_person_id(struct def_vendor *def_vendor);

int acvp_def_get_oe_id(struct def_oe *def_oe);
int acvp_def_put_oe_id(struct def_oe *def_oe);

int acvp_def_get_module_id(struct def_info *def_info);
int acvp_def_put_module_id(struct def_info *def_info);

void acvp_def_release_all(void);

#ifdef __cplusplus
}
#endif

#endif /* DEFINITION_H */
