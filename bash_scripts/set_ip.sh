#!/bin/bash
export MYIP=$(hostname -I | cut -d ' ' -f 1)
echo $MYIP
