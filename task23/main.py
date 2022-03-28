
from transformers import *
from  sklearn.datasets import fetch_20newsgroups
src = "en"
dst = "ru"
task_name = f"translation_{src}_to_{dst}"
model_name = f"Helsinki-NLP/opus-mt-{src}-{dst}"
translator  = pipeline(task_name, model=model_name, tokenizer=model_name)
data = fetch_20newsgroups()
categories = ["sci.med", "sci.space"]
data, _ = fetch_20newsgroups(
    random_state=1,
    subset="test",
    categories=categories,
    remove=('headers', 'footers', 'quotes', ),
    return_X_y=True,
)

import re
k = 0
string_list = []
for text in data[100:]:
    if len(text)>400:
        continue
    rus = translator(text)[0]["translation_text"]
    #print(rus)
    text_list = re.split("([?!.])", rus)
    for string in text_list:
        if len(string)>30:
            string_list.append(string)
            k+=1
            print(k)

    if k > 100:
        break

for K, i in enumerate(string_list):
    print("%s : %s"%(K, i))