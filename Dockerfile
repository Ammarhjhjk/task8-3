FROM gcc:latest

# تثبيت الأدوات الإضافية إذا لزم الأمر
RUN apt-get update && apt-get install -y \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# إنشاء مجلد التطبيق
WORKDIR /usr/src/app

# نسخ ملفات الكود
COPY . .

# ترجمة البرنامج
RUN g++ -o optimus_vs_megatron main.cpp -std=c++11

# الأمر الافتراضي عند تشغيل الحاوية
CMD ["./optimus_vs_megatron"]
