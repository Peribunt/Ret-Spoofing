#include <windows.h>
#include <cstdio>

#define SPOOFER_NOINLINE __declspec( noinline )
#define SPOOFER_INLINE __forceinline

#define CONSOLE_PAUSE( ) \
system( "pause" )

#define CONSOLE_LOG( Fmt, ... ) \
printf( "[!] " __FUNCTION__ ": " Fmt "\n", ##__VA_ARGS__ )

#pragma code_seg( push, ".text" )
__declspec( allocate( ".text" ) )
BYTE JMP_RBX_TEST[] = 
{ 
	0xFF, 0xE3 
};
#pragma code_seg( pop )

namespace ReturnSpoofer
{
	extern "C" 
		ULONG_PTR SpoofCall(
			IN ... );

	extern "C"
		VOID InitSpoofCall(
			IN LPVOID Function,
			IN LPVOID FakeRet );

	template< typename _RET_TYPE_,
		typename... _VA_ARGS_ >
		SPOOFER_NOINLINE
		_RET_TYPE_ WINAPI DoSpoofCall(
			IN LPVOID Function,
			IN LPVOID FakeRet,
			IN OUT _VA_ARGS_... Args OPTIONAL )
		noexcept
	{
		InitSpoofCall( Function, FakeRet );

		return ( ( _RET_TYPE_( * )( IN OUT ... OPTIONAL ) )SpoofCall )
			( Args... );
	}
}

LONG main( VOID )
{
	DWORD Result =
		ReturnSpoofer::DoSpoofCall<DWORD>( MessageBoxA, (PBYTE)JMP_RBX_TEST,
			NULL, "Hello World", "Spoofed call", NULL );

	//
	// Log to prove both execution flow lands here and the value returned properly
	//
	CONSOLE_LOG( "MessageBoxA Result: %i", Result );

	CONSOLE_PAUSE( );

	return NULL;
}
