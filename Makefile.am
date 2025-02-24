# Makefile.am

AUTOMAKE_OPTIONS = foreign subdir-objects

# Define build directory
builddir = build

# Build PAM module as a static library
noinst_LIBRARIES = libpam_evo_common.a
libpam_evo_common_a_SOURCES = src/main.c
# Add -fPIC for position-independent code and proper symbol visibility
libpam_evo_common_a_CFLAGS = -I$(top_srcdir)/include -fPIC -DPAM_EXTERN=extern

# Define installation directories
libdir = /lib/security
configdir = $(sysconfdir)/evosecurity
pamconfdir = /etc/pam.d

# Ensure output goes to build directory
objdir = $(builddir)/obj
all-local:
	@mkdir -p $(builddir)/obj
	@cp src/*.o $(builddir)/obj/
	@cp libpam_evo_common.a $(builddir)/

# Clean build directory
clean-local:
	rm -rf $(builddir)

# Install hook to properly install the PAM module and configuration
install-exec-hook:
	$(MKDIR_P) $(DESTDIR)$(libdir)
	$(MKDIR_P) $(DESTDIR)$(configdir)
	$(MKDIR_P) $(DESTDIR)$(pamconfdir)
	$(CC) -shared -o $(DESTDIR)$(libdir)/pam_evo_common.so \
		$(objdir)/*.o vendor/libevopam.a \
		-Wl,--version-script=pam_symbols.map \
		-lpam -lssl -lcrypto -lm -ldl
	chmod 755 $(DESTDIR)$(libdir)/pam_evo_common.so
	@echo "Creating PAM configuration file..."
	@echo "#%PAM-1.0" > $(DESTDIR)$(pamconfdir)/evo_common
	@echo "auth       required   pam_unix.so" >> $(DESTDIR)$(pamconfdir)/evo_common
	@echo "auth       sufficient pam_evo_common.so" >> $(DESTDIR)$(pamconfdir)/evo_common
	@echo "account    required   pam_unix.so" >> $(DESTDIR)$(pamconfdir)/evo_common
	@echo "session    required   pam_unix.so" >> $(DESTDIR)$(pamconfdir)/evo_common
	chmod 644 $(DESTDIR)$(pamconfdir)/evo_common
	if [ ! -f $(DESTDIR)$(configdir)/config.ini ]; then \
		cp config/config.ini.default $(DESTDIR)$(configdir)/config.ini; \
		chmod 644 $(DESTDIR)$(configdir)/config.ini; \
	fi

# Uninstall hook to clean up
uninstall-hook:
	rm -f $(DESTDIR)$(libdir)/pam_evo_common.so
	rm -f $(DESTDIR)$(pamconfdir)/evo_common
	rm -f $(DESTDIR)$(configdir)/config.ini
