#!/bin/sh
cd ..
tar czf QtSmtpClient-1.1.tar.gz --exclude=*.git* --exclude=*.user --exclude=Makefile* --exclude=Release* --exclude=release* --exclude=Debug* --exclude=debug* ./QtSmtpClient-1.1
