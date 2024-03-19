RED='\033[0;31m'
BLUE='\033[0;34m'
GREEN='\033[0;32m'
NC='\033[0m'

PROBLEM = invalid_courses

PROBLEM_DESCRIPTION = $(PROBLEM)
PROBLEM_ID = $(PROBLEM)
PROBLEM_NAME = $(PROBLEM)

TIME_LIMIT = 5
MEMORY_LIMIT = 256

PROGRAM = $(PROBLEM).py

CFLAGS=-g -Wall
CXXFLAGS=-g -Wall

SHELL=/bin/bash

TIME_LIMIT ?= 1
MEMORY_LIMIT ?= 1024

TIMEOUT_SLACK=3
HARD_TIMEOUT := $(shell expr $(TIME_LIMIT) + $(TIMEOUT_SLACK))
MEMORY_LIMIT_KB := $(shell expr $(MEMORY_LIMIT) \* 1024)

TESTS_DIR=tests
TESTS_IN:=$(wildcard $(TESTS_DIR)/*.in)

.PHONY: all
all: check

TIMER_FORMAT = %e %M

.PHONY: check
check: $(TESTS_IN)
	@exec 2> /dev/null; \
	for p in $(PROGRAM); do \
		echo "Testing $$p, time limit $(TIME_LIMIT)s, memory limit $(MEMORY_LIMIT_KB)KB"; \
		case "$$p" in \
			*.py ) program="python3 $$p" ;; \
			* ) program="`dirname $$p`/$$p" ;; \
		esac ; \
		for t in $(patsubst $(TESTS_DIR)/%.in, %, $(TESTS_IN)); do \
			if test -r "$(TESTS_DIR)/$$t.out"; \
			then \
				t_answer="$(TESTS_DIR)/$$t.out"; \
			elif test -r "$(TESTS_DIR)/$$t.ans"; \
			then \
				t_answer="$(TESTS_DIR)/$$t.ans"; \
			else \
				continue; \
			fi; \
			t_actual=$$(basename "$$t.actual"); \
			t_time=$$(basename "$$t.time"); \
			printf "   test %-40s" "$$t" ; \
			/usr/bin/time -o "$$t_time" -f '$(TIMER_FORMAT)' \
			    $(TIMER_CMD) $$program < "$(TESTS_DIR)/$$t.in" > "$$t_actual" 2>&1 & \
			prog_pid=$$!; \
			( sleep '$(HARD_TIMEOUT)'; kill $$prog_pid > /dev/null 2>&1 ) & \
			killer_pid=$$!; \
			wait $$prog_pid; \
			res=$$?; \
			read time mem < "$$t_time";\
			rm -f "$$t_time";\
			if test $$res -gt 128; \
			then \
				case `kill -l $$(($$res - 128))` in \
					ABRT ) outcome="ABORT";;\
					TERM ) outcome="TIME OUT";;\
					* )    outcome="UNKNOWN";; \
				esac ; \
			else \
				kill $$killer_pid > /dev/null 2>&1 ;\
				wait $$killer_pid; \
				sort < "$$t_answer" > "$$t.a" ; \
				sort < "$$t_actual" > "$$t.b" ; \
				cmp -s "$$t.a" "$$t.b"; \
				if [ $$? = 0 ]; \
				then \
					outcome="PASS";\
				else \
					outcome="FAIL";\
				fi; \
				rm -f "$$t.a" "$$t.b"; \
			fi; \
			if test -n "$$time"; \
			then \
				time_sec=`echo $$time | cut -d . -f 1`; \
				if [ $$time_sec -ge '$(TIME_LIMIT)' ]; \
				then \
					outcome="TIME"; \
					if [ $$mem -ge '$(MEMORY_LIMIT_KB)' ]; \
					then \
						outcome="TIME+MEMORY"; \
					fi; \
				else \
					if [ $$mem -ge '$(MEMORY_LIMIT_KB)' ]; \
					then \
						outcome="MEMORY"; \
					fi; \
				fi;\
				printf "%-10s %6ss %10sKB\n" "$$outcome" "$$time" "$$mem"; \
			else \
				printf "%-10s\n" "$$outcome"; \
			fi; \
			if "$$outcome" = "FAIL";\
			then \
				echo "check diff '$$_actual' '$$t_answer'"; \
			else \
				rm -f "$$t_actual"; \
			fi; \
		done; \
	done

ORACLE=$(firstword $(PROGRAM))

.PHONY: answers
answers: $(patsubst %.in, %.ans, $(TESTS_SECRET))
%.ans: %.in
	$(ORACLE) < $< > $@

.PHONY: clean
.PHONY: clean-testing
clean: clean-testing
clean-testing:
	rm -f *.actual
	@for p in $(PROGRAM); do \
		for ext in cc cpp c ; do \
			if test -x "$$p" -a -r "$$p.$$ext" ; \
			then \
				echo rm "$$p" ; \
				rm "$$p" ; \
				break ; \
			fi ; \
		done ; \
	done

