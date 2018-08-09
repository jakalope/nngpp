#ifndef NNGPP_TRANSPORT_TLS_H
#define NNGPP_TRANSPORT_TLS_H
#include "tls/config.h"
#include <nngpp/listener.h>
#include <nngpp/dialer.h>
#include <nngpp/pipe.h>

extern "C" {
#include <nng/transport/tls/tls.h>
}

namespace nng::tls {

inline void register_transport() {
	int r = nng_tls_register();
	if( r != 0 ) {
		throw exception(r,"nng_tls_register");
	}
}

enum class option {
	config,        // ptr
	auth_mode,     // int
	cert_key_file, // string
	ca_file,       // string
	server_name,   // string
	verified       // bool
};

namespace detail {

inline const char* option_names[] = {
	NNG_OPT_TLS_CONFIG,
	NNG_OPT_TLS_AUTH_MODE,
	NNG_OPT_TLS_CERT_KEY_FILE,
	NNG_OPT_TLS_CA_FILE,
	NNG_OPT_TLS_SERVER_NAME,
	NNG_OPT_TLS_VERIFIED
};

}

inline const char* to_name( option o ) noexcept {
	return detail::option_names[(int)o];
}

inline bool get_opt_verified( pipe_view s ) {
	return s.get_opt_bool( to_name(option::verified) );
}

inline config_view get_opt_config( dialer_view s ) {
	return (nng_tls_config*)s.get_opt_ptr( to_name(option::config) );
}

inline config_view get_opt_config( listener_view s ) {
	return (nng_tls_config*)s.get_opt_ptr( to_name(option::config) );
}

inline void set_opt_config( dialer_view s, config_view v ) {
	s.set_opt_ptr( to_name(option::config), v.get() );
}

inline void set_opt_config( listener_view s, config_view v ) {
	s.set_opt_ptr( to_name(option::config), v.get() );
}

inline void set_opt_auth_mode( dialer_view s, auth_mode v ) {
	s.set_opt_int( to_name(option::auth_mode), (int)v );
}

inline void set_opt_auth_mode( listener_view s, auth_mode v ) {
	s.set_opt_int( to_name(option::auth_mode), (int)v );
}

inline void set_opt_cert_key_file( dialer_view s, const char* v ) {
	s.set_opt_string( to_name(option::cert_key_file), v );
}

inline void set_opt_cert_key_file( listener_view s, const char* v ) {
	s.set_opt_string( to_name(option::cert_key_file), v );
}

inline void set_opt_ca_file( dialer_view s, const char* v ) {
	s.set_opt_string( to_name(option::ca_file), v );
}

inline void set_opt_ca_file( listener_view s, const char* v ) {
	s.set_opt_string( to_name(option::ca_file), v );
}

inline void set_opt_server_name( dialer_view s, const char* v ) {
	s.set_opt_string( to_name(option::server_name), v );
}

inline void set_opt_server_name( listener_view s, const char* v ) {
	s.set_opt_string( to_name(option::server_name), v );
}

}

#endif
