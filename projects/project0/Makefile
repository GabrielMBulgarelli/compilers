CC := gcc
SANCC := clang
CFLAGS := -std=c17 -Wall -Wextra -Wpedantic -Werror -O2
SANFLAGS := -std=c17 -Wall -Wextra -Wpedantic -Werror -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer
SOURCES := main.c scanner.c parser.c semantic.c codegen.c
HEADERS := micro.h scanner.h parser.h semantic.h codegen.h

.PHONY: all clean test test-sanitize verify package

all: micro

micro: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $@

micro-sanitize: $(SOURCES) $(HEADERS)
	$(SANCC) $(SANFLAGS) $(SOURCES) -o $@

test: micro
	@$(MAKE) --no-print-directory run-tests COMPILER="$(CURDIR)/micro"

test-sanitize: micro-sanitize
	@ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1 \
		$(MAKE) --no-print-directory run-tests COMPILER="$(CURDIR)/micro-sanitize"

.PHONY: run-tests
run-tests:
	@set -eu; \
	tmp=$$(mktemp -d); \
	trap 'rm -R -- "$$tmp"' EXIT HUP INT TERM; \
	cp tests/*.micro "$$tmp/"; \
	cp examples/example.micro "$$tmp/example.micro"; \
	out=$$("$(COMPILER)" "$$tmp/valid_min.micro"); \
	test -z "$$out"; \
	out=$$("$(COMPILER)" "$$tmp/arithmetic.micro"); \
	test "$$out" = "$$(printf '3\n2\n7\n9\n3')"; \
	out=$$("$(COMPILER)" "$$tmp/symbols.micro"); \
	test "$$out" = "$$(printf '1\n2\n3\n4')"; \
	out=$$(printf '4 5\n' | "$(COMPILER)" "$$tmp/io.micro"); \
	test "$$out" = "$$(printf '4\n5')"; \
	out=$$("$(COMPILER)" "$$tmp/comments.micro"); \
	test "$$out" = "3"; \
	out=$$("$(COMPILER)" "$$tmp/constant.micro"); \
	test "$$out" = "0"; \
	out=$$("$(COMPILER)" "$$tmp/identifier_forms.micro"); \
	test "$$out" = "$$(printf '2147483647\n-2147483648')"; \
	out=$$(printf '2 3\n' | "$(COMPILER)" "$$tmp/example.micro"); \
	test "$$out" = "5"; \
	for bad in empty malformed bad_char bad_identifier long_identifier long_literal fold_overflow; do \
		if "$(COMPILER)" "$$tmp/$$bad.micro" >/dev/null 2>&1; then \
			echo "expected $$bad.micro to fail" >&2; exit 1; \
		fi; \
		test ! -e "$$tmp/$$bad.s"; \
	done; \
	grep -q 'micro_var_main' "$$tmp/symbols.s"; \
	grep -q 'micro_var_printf' "$$tmp/symbols.s"; \
	grep -q 'micro_var_scanf' "$$tmp/symbols.s"; \
	grep -q 'micro_var_Temp1' "$$tmp/symbols.s"; \
	grep -q 'micro_tmp_' "$$tmp/arithmetic.s"; \
	if grep -q 'micro_tmp_' "$$tmp/constant.s"; then \
		echo 'constant expression unexpectedly allocated a temporary' >&2; exit 1; \
	fi; \
	grep -q '^\.section \.note\.GNU-stack,"",@progbits$$' "$$tmp/arithmetic.s"; \
	grep -Fq '	pushq %rbp' "$$tmp/arithmetic.s"; \
	grep -Fq '	movl $$0, %eax' "$$tmp/arithmetic.s"; \
	grep -Fq '	xorl %eax, %eax' "$$tmp/io.s"; \
	grep -Fq '	leaq micro_var_first(%rip), %rsi' "$$tmp/io.s"; \
	grep -Fq '	call scanf@PLT' "$$tmp/io.s"; \
	grep -Fq '	call printf@PLT' "$$tmp/io.s"; \
	false_line=$$(grep -n '^\.Lmicro_false_' "$$tmp/arithmetic.s" | head -1 | cut -d: -f1); \
	end_line=$$(grep -n '^\.Lmicro_end_' "$$tmp/arithmetic.s" | head -1 | cut -d: -f1); \
	branch_line=$$(grep -n 'je \.Lmicro_false_' "$$tmp/arithmetic.s" | head -1 | cut -d: -f1); \
	jump_line=$$(grep -n 'jmp \.Lmicro_end_' "$$tmp/arithmetic.s" | head -1 | cut -d: -f1); \
	test "$$branch_line" -lt "$$jump_line"; \
	test "$$jump_line" -lt "$$false_line"; \
	test "$$false_line" -lt "$$end_line"; \
	test "$$(grep -c '^\.Lmicro_false_[0-9][0-9]*:' "$$tmp/arithmetic.s")" -eq 4; \
	test "$$(grep -c '^\.Lmicro_end_[0-9][0-9]*:' "$$tmp/arithmetic.s")" -eq 4; \
	test "$$(grep '^\.Lmicro_\(false\|end\)_[0-9][0-9]*:' "$$tmp/arithmetic.s" | sort -u | wc -l)" -eq 8; \
	cp tests/valid_min.micro "$$tmp/foo.micro"; \
	"$(COMPILER)" "$$tmp/foo.micro" >/dev/null; \
	test -f "$$tmp/foo.s"; test -x "$$tmp/foo"; \
	cd "$$tmp"; \
	cp valid_min.micro .micro; \
	"$(COMPILER)" .micro >/dev/null; \
	test -f .micro.s; test -x .micro.out; \
	cp valid_min.micro x; \
	"$(COMPILER)" x >/dev/null; \
	test -f x.s; test -x x.out; \
	cp valid_min.micro -- -test.micro; \
	"$(COMPILER)" -test.micro >/dev/null; \
	test -f ./-test.s; test -x ./-test; \
	mkdir "path with spaces and 'quote'"; \
	cp valid_min.micro "path with spaces and 'quote'/safe.micro"; \
	"$(COMPILER)" "path with spaces and 'quote'/safe.micro" >/dev/null; \
	test -f "path with spaces and 'quote'/safe.s"; \
	rm -f valid_min.s valid_min; \
	if PATH=/nonexistent "$(COMPILER)" valid_min.micro >/dev/null 2>&1; then \
		echo 'expected missing gcc to fail' >&2; exit 1; \
	fi; \
	test -f valid_min.s; test ! -e valid_min; \
	echo 'all regression tests passed'

verify: test test-sanitize

package: verify
	@cd .. && tar -czf proyecto0.tgz \
		--exclude='project0/micro' \
		--exclude='project0/micro-sanitize' \
		--exclude='project0/*.o' \
		--exclude='project0/examples/*.s' \
		--exclude='project0/examples/example' \
		project0; \
	tmp=$$(mktemp -d); \
	trap 'rm -R -- "$$tmp"' EXIT HUP INT TERM; \
	tar -xzf proyecto0.tgz -C "$$tmp"; \
	test "$$(tar -tzf proyecto0.tgz | sed 's,/.*,,' | sort -u)" = project0; \
	$(MAKE) --no-print-directory -C "$$tmp/project0" verify

clean:
	rm -f micro micro-sanitize *.o examples/*.s examples/example
