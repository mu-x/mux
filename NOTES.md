# Just a Note Pad

## First things to do on Windows 10

Useful Soft:
- Git Bash: https://git-scm.com
- Total Commander: https://www.ghisler.com/download.htm
- Virtual Box: https://www.virtualbox.org/wiki/Downloads
- Visual Studio (+Code): https://visualstudio.microsoft.com

Explorer (Win+E - View - Options):
- View - Hide extensions for known file types


## Mercurial (hg) for git user

```
    hg pull --rebase        # git pull && get rebase NEW_HEAD
    hg branches             # git branch
    hg update BRANCH        # git checkout BRANCH
    hg branch NEW_BRANCH    # git checkout -b NEW_BRANCH
    hg push [--new-branch]  # git push
    hg graft CHANGE_ID ...  # git cherry-pick CHANGE_ID
    hg log -b .             # git log
```
