import random
from faker import Faker

fake = Faker('zh_CN')

lesson_names = [
    '高等数学', '抽象代数', '离散数学', '计算机图形学', '人工智能',
    '概率论', '数据库系统', '操作系统', '编译原理', '线性代数', '网络安全'
]

def generate_teacher_data(num_teachers):
    data = []
    for _ in range(num_teachers):
        teacher_id = random.randint(1, 100)
        name = fake.name()
        gender = random.choice(['男', '女'])
        year = random.randint(1960, 2000)
        month = random.randint(1, 12)
        day = random.randint(1, 28)
        rank = random.choice(['教授', '副教授', '讲师', '助教'])
        degree = random.choice(['博士', '硕士'])
        salary = random.randint(16, 80) * 500
        is_married = random.choice(['已婚', '未婚'])

        teacher_info = f"{teacher_id} {name} {gender} {year} {month} {day} {rank} {degree} {salary} {is_married} |"

        lesson_info = ""
        num_lessons = random.randint(1, 3)
        for _ in range(num_lessons):
            lesson_id = random.randint(1, 200)
            lesson_name = random.choice(lesson_names)
            last_time = random.randint(1, 6) * 16

            building = f"J{random.randint(1, 4)}"
            room_number = f"{random.randint(1, 4)}0{random.randint(0, 9)}"
            classroom = f"{building}-{room_number}"

            class_group = str(random.randint(581230, 581239))
            gpa = random.randint(1,8)*0.5
            semester = random.randint(1, 8)

            lesson_info += f"{lesson_id} {lesson_name} {last_time} {classroom} {class_group} {gpa} {semester} "

        data.append(teacher_info + lesson_info)

    return data

def write_to_file(filename, data):
    with open(filename, 'w') as file:
        for line in data:
            file.write(line + '\n')

filename = 'D:\\data2.txt'
teacher_data = generate_teacher_data(10)
write_to_file(filename, teacher_data)

