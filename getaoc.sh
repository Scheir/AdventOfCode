#!/bin/bash
if [ "$#" -eq 1 ]; then
	curl https://adventofcode.com/2021/day/$1/input --cookie "session=53616c7465645f5f5efa122c04f93c18c4585e21a3f7c9b3f353a6c46b6ff3ec8fa6b6f45281e0cda6d3a2fceb1a9b33"
	exit 0
fi
if [ "$#" -eq 2 ]; then
	curl https://adventofcode.com/20$2/day/$1/input --cookie "session=53616c7465645f5f5efa122c04f93c18c4585e21a3f7c9b3f353a6c46b6ff3ec8fa6b6f45281e0cda6d3a2fceb1a9b33"
	exit 0
fi

echo "To few arguments, d req, yy optional"
