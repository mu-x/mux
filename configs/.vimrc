" basics
set number
set clipboard=unnamedplus

" indentation
set cindent tabstop=4 shiftwidth=4 expandtab

" clear text after insertion
autocmd InsertLeave * :%s/\s\+$//ge
autocmd InsertLeave * :%s/\t/    /ge

