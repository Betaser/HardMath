param (
    $file = $null
)

if ($file) {
    $fileNoExt = (Get-Item $file).BaseName
    clang++ $file -o $fileNoExt; & "./$fileNoExt.exe"
}
