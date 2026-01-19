from cs50 import get_string
text = get_string("Text: ").lower()
length = len(text)
letters = 0
sentences = 0
words = 1
for i in range(0, length, 1):
    if text[i] == " ":
        words += 1
    elif text[i] == "." or text[i] == "!" or text[i] == "?":
        sentences += 1
    elif text[i] >= "a" and text[i] <= "z":
        letters += 1
S = sentences / words * 100
L = letters / words * 100
Coleman = round(0.0588 * L - 0.296 * S - 15.8)
if Coleman < 0:
    print("Before Grade 1")
elif Coleman > 16:
    print("Grade 16+")
else:
    print(f"Grade {Coleman}")
