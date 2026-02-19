Embedded Tensor Quantization Demo
-Bu depo, yüksek hassasiyetli floating-point (FP32) verilerin, bellek ve işlemci kısıtı olan gömülü sistemlerde kullanılmak üzere 8-bit tam sayı (INT8) formatına nasıl dönüştürüldüğünü gösteren bir C uygulaması içerir.



📖 Kuantizasyon Nedir ve Neden Gereklidir?
Yapay zeka modelleri genellikle yüksek hassasiyetli kayan noktalı sayılarla (FP32) eğitilir. Ancak bu modelleri bir mikrodenetleyici (örneğin STM32 veya ESP32) üzerinde çalıştırmak istediğimizde iki ana engel ile karşılaşırız:

Sınırlı Bellek (RAM/Flash): Bir float değeri 4 byte yer kaplar.

Hesaplama Gücü: Birçok düşük maliyetli mikrodenetleyicinin FPU (Floating Point Unit) birimi yoktur veya tamsayı aritmetiği kadar hızlı değildir.

Kuantizasyon, bu 4 byte'lık değerleri 1 byte'lık (INT8) değerlere indirgeyerek model boyutunu %75 oranında küçültür ve işlem hızını artırır.



🛠️ Kod Yapısı ve Mimari
Kod, profesyonel gömülü sistem projelerinde kullanılan esnek bir yapıya sahiptir:

Union & Struct Kullanımı: TensorData union yapısı sayesinde bellek verimli bir şekilde yönetilir.

Dinamik Bellek: create_tensor fonksiyonu ile çalışma zamanında (heap) yer ayrılır.

Bellek Analizi: Program, işlem sonunda sağlanan net bayt kazancını raporlar.



📝 Lisans ve Geliştirici
Bu proje, Yusuf Cezlan tarafından gömülü sistemlerde AI optimizasyonlarını (TinyML) öğrenmek ve göstermek amacıyla geliştirilmiştir.

