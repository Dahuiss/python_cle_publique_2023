import voiture_component

ma_bagnole = voiture_component.Voiture("Ferrari" , 10)
print(f"ma voiture: {ma_bagnole.get_nom()}")
print(f"carburant initial: {str(ma_bagnole.get_volumeEssence())}")
print("je roule un peu")
ma_bagnole.roule()
print(f"carburant final: {str(ma_bagnole.get_volumeEssence())}")
