
``` mermaid
%%{ init: {
  "theme": "default",
  "themeVariables": {
    "git0": "#00ff00",
    "git1": "#00ff00",
    "git2": "#00ff00",
    "git3": "#ff0000",
    "git4": "#ff0000",
    "git5": "#ff0000",
    "git6": "#ff0000",
    "git7": "#ff0000"
  },
  "gitGraph": {
    "showCommitLabel": true
  }
}
}%%
gitGraph
  commit id: "1.2.0" tag: "v1.2.0"
  branch develop order:1
  commit id: "1.3.0-alpha.1"
  branch pull/2/merge order:1
  commit id: "1.3.0-pr.2+2"
  checkout develop
  merge pull/2/merge tag: "1.3.0-alpha.2"
  checkout main
  branch hotfix/1.2.1 order:1
  commit id: "1.2.1-beta.1"
  checkout main
  merge hotfix/1.2.1 tag: "v1.2.1"
  checkout develop
  merge hotfix/1.2.1 tag: "1.3.0-alpha.3"
  branch release/1.3.0 order:1
  commit id: "1.3.0-beta.1"
  commit id: "1.3.0-beta.2"
  checkout main
  merge release/1.3.0 tag: "v1.3.0"
  branch support/1.3 order:0
  checkout develop
  merge release/1.3.0 tag: "1.4.0-alpha.1"
  branch release/2.0.0 order:1
  commit id: "2.0.0-beta.1"
  commit id: "2.0.0-beta.2"
  checkout main
  merge release/2.0.0 tag: "v2.0.0"
  checkout develop
  merge release/2.0.0 tag: "v2.1.0-alpha.1"
  checkout support/1.3
  branch hotfix/1.3.1 order:1
  commit id: "1.3.1-beta.1"
  checkout support/1.3
  merge hotfix/1.3.1 tag: "v1.3.1"
  ```