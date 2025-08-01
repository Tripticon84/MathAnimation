# GitHub Actions Workflows

Ce répertoire contient les workflows GitHub Actions pour automatiser la compilation et les releases de MathAnimation.

## Workflows disponibles

### 1. `build-and-release.yml` - Build et Release automatique

Ce workflow se déclenche automatiquement lors de la création d'un nouveau tag version (ex: `v1.0.0`) et :

- Compile le projet pour Windows et Linux
- Crée des archives prêtes à distribuer
- Publie automatiquement une nouvelle release GitHub avec les binaires

**Utilisation :**
```bash
# Créer et pousser un tag version
git tag v1.0.0
git push origin v1.0.0
```

Le workflow peut aussi être déclenché manuellement depuis l'interface GitHub Actions.

### 2. `ci.yml` - Intégration Continue

Ce workflow se déclenche à chaque push/PR sur les branches principales et :

- Compile le projet pour vérifier qu'il n'y a pas d'erreurs
- Exécute les tests (si disponibles)
- Valide que le code compile correctement sur Windows et Linux

## Plateformes supportées

- **Windows** : Windows 10/11 64-bit (Visual Studio 2022)
- **Linux** : Ubuntu 22.04+ 64-bit (GCC + Ninja)

## Prérequis

### Pour Windows :
- CMake 3.24.2+
- YASM (téléchargé automatiquement)
- Visual Studio 2022 (installé automatiquement sur le runner)

### Pour Linux :
- CMake 3.24.2+
- YASM
- Dépendances système (OpenGL, ALSA, X11, etc.)

## Configuration

Les workflows sont configurés pour :

- Utiliser une compilation en mode `Release` par défaut
- Inclure tous les sous-modules Git de façon récursive
- Packager les assets, documentation et fichiers de licence
- Créer des archives optimisées pour la distribution

## Artefacts générés

Les builds génèrent les artefacts suivants :

- `MathAnimation-Windows-x64.zip` : Version Windows complète
- `MathAnimation-Linux-x64.tar.gz` : Version Linux complète

Chaque archive contient :
- L'exécutable principal
- Les bibliothèques nécessaires
- Le dossier `assets/` avec toutes les ressources
- La documentation (`README.md`, `EULA.txt`)

## Sécurité

Les workflows utilisent uniquement le token GitHub par défaut (`GITHUB_TOKEN`) et ne nécessitent aucune configuration de secrets supplémentaires.
