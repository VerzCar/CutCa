astyle ^
--recursive ^
--add-braces ^
--attach-return-type ^
--style=allman ^
-s4 --indent=spaces=4 ^
 --indent-modifiers ^
--indent-switches ^
--indent-preproc-block ^
--indent-col1-comments ^
--min-conditional-indent=2 ^
--max-continuation-indent=60 ^
--break-blocks  ^
--pad-oper --pad-comma ^
--pad-header ^
--align-pointer=type ^
--align-reference=type ^
--max-code-length=120 --options=file/allman.ini ../../Editor/*.cpp,*.hpp,*.c,*.h ../../Cutter/*.cpp,*.hpp,*.h
pause