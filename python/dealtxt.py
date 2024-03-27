# 定义输入文件名和输出文件名
input_file = "a.txt"
output_file = "output.txt"

# 定义要搜索的关键字
keyword = "location, ax is"

# 打开输入文件进行读取
with open(input_file, "r") as infile:
    # 打开输出文件进行写入
    with open(output_file, "w") as outfile:
        # 逐行读取输入文件
        for line in infile:
            # 检查关键字是否在当前行中
            if keyword in line:
                # 将包含关键字的行写入输出文件
                outfile.write(line)