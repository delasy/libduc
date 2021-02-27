result = '#define DUC_NUMBERS_1024_ 1024'
result_llen = len(result)

for i in reversed(range(0, 1024)):
    ch = str(i)
    ch_len = len(ch)

    if result_llen + ch_len + 5 >= 80:
        result += ', \\\n  ' + ch
        result_llen = ch_len + 2
    else:
        result += ', ' + ch
        result_llen += ch_len + 2

result += '\n'
print(result)

result = '#define DUC_NARG1024_(_1'
result_llen = len(result)

for i in range(2, 1025):
    ch = '_' + str(i)
    ch_len = len(ch)

    if result_llen + ch_len + 5 >= 80:
        result += ', \\\n  ' + ch
        result_llen = ch_len + 2
    else:
        result += ', ' + ch
        result_llen += ch_len + 2

result += ', N, ...) N'
print(result)
