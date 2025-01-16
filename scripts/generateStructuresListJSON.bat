@echo off

set "active_dir=src\structures\activeStructures"
set "passive_dir=src\structures\passiveStructures"
set "output_file=data\structuresList.json"

:: Crée le fichier JSON
(echo {)> "%output_file%"
(echo   "activeStructures": [) >> "%output_file%"

setlocal enabledelayedexpansion
set first=true

:: Parcours des fichiers dans activeStructures
for %%F in (%active_dir%\*.cpp) do (
    set "filename=%%~nF"
    if "!first!" == "true" (
        (echo     "!filename!") >> "%output_file%"
        set "first=false"
    ) else (
        (echo     ,"!filename!") >> "%output_file%"
    )
)

(echo   ],) >> "%output_file%"
(echo   "passiveStructures": [) >> "%output_file%"

set first=true

:: Parcours des fichiers dans passiveStructures
for %%F in (%passive_dir%\*.cpp) do (
    set "filename=%%~nF"
    if "!first!" == "true" (
        (echo     "!filename!") >> "%output_file%"
        set "first=false"
    ) else (
        (echo     ,"!filename!") >> "%output_file%"
    )
)

(echo   ]) >> "%output_file%"
(echo }) >> "%output_file%"

endlocal

:: Affiche un message de succès
echo File created: %output_file%
