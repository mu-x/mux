" basics
set number
set clipboard=unnamedplus
set encoding=utf-8
set fileencoding=utf8

" indentation
set cindent tabstop=4 shiftwidth=4 expandtab

" clear text after insertion
autocmd InsertLeave * :%s/\s\+$//ge
autocmd InsertLeave * :%s/\t/    /ge

" extra functions

function SyntaxExtraHi()
  syn match Operators display '[{}()<>\[\]\+\-\*\=\&\*\$\^\:\~\,\.\;]'
  hi Operators ctermfg=3

  syn match Tabs display '\t'
  hi Tabs ctermbg=3
endfunction

autocmd Syntax * :call SyntaxExtraHi()

