from cs50 import get_float
coins = [25, 10, 5, 1]
while True:
    change = get_float("Change: ")
    if change > 0:
        break
min_coin = 0
change = round(change * 100)
for i in coins:
    while change >= i:
        change -= i
        min_coin += 1
print(min_coin)
