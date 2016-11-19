(echo a && echo b || ls-a) || echo why
echo hello || (echo a && echo b || ls-a)
(mkdir nick) && (echo hello ; ls -a)
ehco 56|| (mkdir fail && echo fail && echo failure)
ls -a || ( echo hello world || mkdir cat && conrats) || echo we did it
(echo hello) || (echo flavor && echo boop) || ( test -e /test/file/path )
