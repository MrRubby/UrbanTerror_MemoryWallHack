Referenced in 

Urban Terror 4.3.4 için, derinlik testini devre dışı bırakarak varlıkları duvarlardan ortaya çıkaran bir wallhack.

Bu, her bir varlığın nasıl işlenmesi gerektiğini belirlemekten sorumlu olan oluşturma bayrağını değiştirerek yapılır. Bu değer, devre dışı bırakılmış derinlik testi için oyun içi değere ayarlandığında (0xD), varlıklar görünür olup olmamaları gerekip gerekmediğine göre çizilir. Hooked kodu, ebx geçerli bir varlık yapısıyla yüklendikten sonra oluşan bir mov talimatıdır.

Bunun işe yaraması için Kentsel Terör sürecine enjekte edilmesi gerekiyor. Bunu yapmanın bir yolu bir DLL enjektörü kullanmaktır. Başka bir yol, kayıt defterinde AppInit_DLLs etkinleştirmektir.
