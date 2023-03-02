#include <Windows.h>

DWORD ret_address = 0x0052D303;

// Program yürütmenin atlayacağı codecave kodekimiz. declspec çıplak özniteliği derleyiciye herhangi bir işlev eklememesini söyler
// Birleştirilmiş kodun etrafındaki başlıklar
__declspec(naked) void codecave() {
	// Asm blokları saf montaj yazmanızı sağlar
	// Bu durumda, tüm kayıtları kaydetmek için kullanırız
	// Ardından varlığın oluşturma değerini [ebx+4] konumunda devre dışı derinlik testine ayarlayın (0xD)
	// Sonra kayıtları geri yükleriz, orijinal talimatı yeniden oluştururuz ve program koduna geri atlarız.
	__asm {
		pushad
		mov dword ptr ds:[ebx+4], 0xD
		popad
		mov dword ptr ds:[0x102AE98], ebx

		jmp ret_address
	}
}

// DLL'miz eklendiğinde, yazmak istediğimiz koddaki belleğin korumasını kaldırın
// Ardından ilk opcode'u E9 olarak ayarlayın veya atlayın
// Formülü kullanarak konumu katulalayın: new_location - original_location+5
// Son olarak, orijinal talimatlar toplam 6 bayt olduğundan, kalan son baytı NOP
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	DWORD old_protect;
	unsigned char* hook_location = (unsigned char*)0x0052D2FD;

	if (fdwReason == DLL_PROCESS_ATTACH) {
		VirtualProtect((void*)hook_location, 5, PAGE_EXECUTE_READWRITE, &old_protect);
		*hook_location = 0xE9;
		*(DWORD*)(hook_location + 1) = (DWORD)&codecave - ((DWORD)hook_location + 5);
		*(hook_location + 5) = 0x90;
	}

	return true;
}
