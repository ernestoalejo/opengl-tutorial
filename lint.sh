
FILTER="-runtime/references,-whitespace/labels,-readability/streams,\
-legal/copyright,-build/header_guard"

if [ "$1" = "" ]; then
  find -name '*.cc' -o -name '*.h' | xargs 'cpplint.py' --filter=$FILTER
else
  cpplint.py --filter=$FILTER $1
fi
