#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// 1. Veri Tipleri ve Yapi Tanimlari
typedef enum { TENSOR_FLOAT32, TENSOR_INT8 } TensorType;

typedef union {
    float* f32;
    int8_t* i8;
    float* result;
} TensorData;

typedef struct {
    TensorData data;
    TensorType type;
    size_t length;
    float scale;
} Tensor;


// --- Yardimci Fonksiyonlar ---


Tensor create_tensor(size_t n, TensorType type) {
    Tensor t;
    t.length = n;
    t.type = type;
    if (type == TENSOR_FLOAT32) {
        t.data.f32 = (float*)malloc(n * sizeof(float));
    } else {
        t.data.i8 = (int8_t*)malloc(n * sizeof(int8_t));
    }
    return t;
}


void quantize_action(Tensor* f_tensor, Tensor* i_tensor) {
    int j;
    for (j = 0; j < (int)f_tensor->length; j++) {
    	
        // Quantization Formulu: Q = V / S
        // Float degeri scale katsayisina bolerek 8-bit tam sayiya indiriyoruz.
        i_tensor->data.i8[j] = (int8_t)(f_tensor->data.f32[j] / i_tensor->scale);
    }
}

int main() {
    int i;
    int input_count;
    float temp_val;
    Tensor input_float, quantized_int8;


    printf("=== Veri Giris Paneli ===\n");
    
    
    // --- 1. Eleman Sayisini Al ---
    printf("Kac adet veri gireceksiniz? (Orn: 3): ");
    if (scanf("%d", &input_count) != 1) return 1;


    // Tensorleri bellekten (Heap) olustur (ram öbek)
    input_float = create_tensor(input_count, TENSOR_FLOAT32);
    quantized_int8 = create_tensor(input_count, TENSOR_INT8);
    
    // Scale degeri: Veriyi -128 ile 127 arasina sigdirmak icin kullanilir.
    
    quantized_int8.scale = 0.05f; 


    // 2. Kullanicidan Verileri Al (Orn: 0.5, 1.2, -0.9)
    
    printf("\n--- Veri Girisi Basladi ---\n");
    for(i = 0; i < input_count; i++) {
        printf("%d. veriyi giriniz: ", i + 1);
        scanf("%f", &temp_val);
        input_float.data.f32[i] = temp_val;     
    }


    // 3. Islem: Float veriyi Int8'e sikistir
    
    quantize_action(&input_float, &quantized_int8);

    // 4. Sonuclari Yazdir
    printf("\n--- Islem Sonuclari ---\n");
    printf("Orijinal (Float32): ");
    for(i = 0; i < input_count; i++) printf("%.2f ", input_float.data.f32[i]);

    printf("\nSikistirilmis (Int8): ");
    for(i = 0; i < input_count; i++) printf("%d ", quantized_int8.data.i8[i]);

    // 5. Bellek Analizi 
    
    printf("\n\n--- Gomulu Sistem Bellek Analizi ---");
    printf("\nFloat32 Bellek Kullanimi: %lu Byte", (unsigned long)(input_count * sizeof(float)));
    printf("\nInt8 Bellek Kullanimi   : %lu Byte", (unsigned long)(input_count * sizeof(int8_t)));
    printf("\nNet Bellek Kazanci      : %%%.0f\n", (1.0f - (float)sizeof(int8_t)/sizeof(float)) * 100);
    
    // Bellek temizligi (Memory Management)
    
    free(input_float.data.f32);
    free(quantized_int8.data.i8);

    printf("\nCikis icin Enter'a basin...");
    fflush(stdin); getchar(); getchar();
    return 0;
}
