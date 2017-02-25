none: help

help:
	@echo "=== Stormsound 1.0 ==="
	@echo "Select a build target:"
	@echo "  make ready             Build Stormsound and bundles it for distribution."
	@echo "  make clean             Clean up Stormsound and Tester."
	@echo "  make cleandebug        Clean up Stormsound and Tester Debug."
	@echo "  make cleanrelease      Clean up Stormsound and Tester Release."
	@echo "  make docs              Generate HTML docs."
	@echo "  make docs_pdf          Generate PDF docs."
	@echo "  make stormsound        Build Stormsound as release."
	@echo "  make stormsound_debug  Build Stormsound as debug."
	@echo "  make tester            Build Stormsound Tester (+Stormsound) as release."
	@echo "  make tester_debug      Build Stormsound Tester (+Stormsound) as debug."
	@echo "  make all               Build everything."
	@echo "  make allfresh          Clean and rebuild everything."
	@echo
	@echo "Clang Sanitizers (requires Debug build and Clang.)"
	@echo "  SAN=address     Use AddressSanitizer"
	@echo "  SAN=leak        Use LeakSanitizer w/o AddressSanitizer (Linux only)"
	@echo "  SAN=memory      Use MemorySanitizer"
	@echo "  SAN=thread      Use ThreadSanitizer"
	@echo "  SAN=undefined   Use UndefiniedBehaviorSanitizer"
	@echo
	@echo "Optional Architecture"
	@echo "  ARCH=32         Make x86 build (-m32)"
	@echo "  ARCH=64         Make x64 build (-m64)"
	@echo
	@echo "Use Configuration File"
	@echo "  CONFIG=foo      Uses the configuration file 'foo.config'"
	@echo "                  in the root of this repository."
	@echo "  When unspecified, default.config will be used."
	@echo
	@echo "For other build options, see the 'make' command in 'docs/', 'stormsound-source/', and 'stormsound-tester/'."

clean:
	$(MAKE) clean -C stormsound-source
	$(MAKE) clean -C stormsound-tester

cleanall: clean
	$(MAKE) clean -C docs

cleandebug:
	$(MAKE) cleandebug -C stormsound-source
	$(MAKE) cleandebug -C stormsound-tester

cleanrelease:
	$(MAKE) cleanrelease -C stormsound-source
	$(MAKE) cleanrelease -C stormsound-tester

docs:
	$(MAKE) html -C docs
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "View docs at 'docs/build/html/index.html'."
	@echo "-------------"

docs_pdf:
	$(MAKE) latexpdf -C docs
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "View docs at 'docs/build/latex/Stormsound.pdf'."
	@echo "-------------"

stormsound:
	$(MAKE) release ARCH=$(ARCH) CONFIG=$(CONFIG) -C stormsound-source
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "Stormsound is in 'stormsound-source/lib/Release'."
	@echo "-------------"

stormsound_debug:
	$(MAKE) debug ARCH=$(ARCH) CONFIG=$(CONFIG) SAN=$(SAN) -C stormsound-source
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo  on "Stormsound is in 'stormsound-source/lib/Debug'."
	@echo "-------------"

ready: stormsound
	@rm -rf stormsound
	@echo "Creating file structure..."
	@mkdir -p stormsound/lib
	@echo "Copying Stormsound..."
	@cp -r stormsound-source/include stormsound/
	@cp stormsound-source/lib/Release/libstormsound.a stormsound/lib/libstormsound.a
	@echo "Copying README and LICENSE..."
	@cp README.md stormsound/README.md
	@cp LICENSE.md stormsound/LICENSE.md
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "The libraries are in 'stormsound'."
	@echo "-------------"

tester: stormsound
	$(MAKE) release ARCH=$(ARCH) CONFIG=$(CONFIG) -C stormsound-tester
	@rm -f tester
	@ln -s stormsound-tester/bin/Release/stormsound-tester tester
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "Stormsound Tester is in 'stormsound-tester/bin/Release'."
	@echo "The link './tester' has been created for convenience."
	@echo "-------------"


tester_debug: stormsound_debug
	$(MAKE) debug ARCH=$(ARCH) CONFIG=$(CONFIG) SAN=$(SAN) -C stormsound-tester
	@rm -f tester_debug
	@ln -s stormsound-tester/bin/Debug/stormsound-tester tester_debug
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "Stormsound Tester is in 'stormsound-tester/bin/Debug'."
	@echo "The link './tester_debug' has been created for convenience."
	@echo "-------------"

all: docs tester

allfresh: cleanall all

.PHONY: all allfresh clean cleanall cleandebug cleanrelease docs docs_pdf stormsound stormsound_debug ready tester tester_debug
