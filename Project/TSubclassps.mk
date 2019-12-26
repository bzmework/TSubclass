
TSubclassps.dll: dlldata.obj TSubclass_p.obj TSubclass_i.obj
	link /dll /out:TSubclassps.dll /def:TSubclassps.def /entry:DllMain dlldata.obj TSubclass_p.obj TSubclass_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del TSubclassps.dll
	@del TSubclassps.lib
	@del TSubclassps.exp
	@del dlldata.obj
	@del TSubclass_p.obj
	@del TSubclass_i.obj
