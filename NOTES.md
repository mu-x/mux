# Just a note pad

## Maven for C++ dummies

```
    mvn compile     # Generate make files
    mvn package     # Build binaries

    -Dbuild.configuration=debug     # debug mode
    --projects P1[,P2[,...]]        # affect only projects
```

## Mercurial (hg) for git user

```
    hg branches             # git branch
    hg update BRANCH        # git checkout BRANCH
    hg branch NEW_BRANCH    # git checkout -b NEW_BRANCH
    hg push [--new-branch]  # git push
    hg graft CHANGE_ID ...  # git cherry-pick CHANGE_ID
    hg log -b .             # git log
```
