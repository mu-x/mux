# Network Optix Notepad

## Project Build & run

mvn compile -Dbuild.configuration=debug
mvn package -Dbuild.configuration=debug

## Mercurial (Hg) Tips

```
    hg branches             # git branch
    hg update BRANCH        # git checkout BRANCH
    hg branch NEW_BRANCH    # git checkout -b NEW_BRANCH
    hg push [--new-branch]  # git push
    hg graft CHANGE_ID ...  # git cherry-pick CHANGE_ID
```


## Code notes

NX_LOG -- for errors
Q_ASSERT -- for fatals
