REM  *****  BASIC  *****

Sub Main


' VerifInvariables () ' pour effacer les colonnes apres les invariables
' SupprimeNombreVide () ' pour supprimer les colonne qui non pas de nombre (dessous-de-table par exemple)
' FabriqueDuPluriel () ' on insere et copie et on vide
' PrepaC () ' pour fabriquer le tableau C pour le logiciel
			'  !!!  !!!  !!!  Faire de la place en inserant les 
			'  !!!  !!!  !!!  colonnes a la main dans une feuille GENRE&NOMBRES_CSV

End Sub

Sub PrepaC

	Dim oDoc As Object, oFeuille As Object
	Dim strCEllule As String
	
	Dim iLigne As Integer
	
	
' On récupere le document
	oDoc = ThisComponent
' On récupere la feuille de LE mon document
	oFeuille = oDoc.Sheets.getByName("GENRE&NOMBRE_C")
	
	iLigne = 0
	
	strCEllule = oFeuille.getCellByPosition(1,iLigne).String
	
	Do While (strCEllule <> "")		

		oFeuille.getCellByPosition(0,iLigne).String = "{"""

		oFeuille.getCellByPosition(2,iLigne).String = """, """
		
		if oFeuille.getCellByPosition(5,iLigne).String = "" then
		
			oFeuille.getCellByPosition(4,iLigne).String = """}, "
		
		else
			oFeuille.getCellByPosition(4,iLigne).String = """, """
			oFeuille.getCellByPosition(6,iLigne).String = """}, "
		
		end if
		
		
		iLigne = iLigne+1
		
		strCEllule = oFeuille.getCellByPosition(1,iLigne).String
	Loop	


End Sub

Sub SupprimeNombreVide ()

	Dim oDoc As Object, oFeuille As Object
	Dim strCEllule As String
	
	Dim strCelluleC As String, strCelluleD As String
	
	Dim iLigne As Integer
	
	
' On récupere le document
	oDoc = ThisComponent
' On récupere la feuille de LE mon document
	oFeuille = oDoc.Sheets.getByName("GENRE&NOMBRE")
	
	iLigne = 0
	
	strCEllule = oFeuille.getCellByPosition(0,iLigne).String

	
	Do While (strCEllule <> "")

		strCelluleC = oFeuille.getCellByPosition(2,iLigne).String
		strCelluleD = oFeuille.getCellByPosition(3,iLigne).String
		

		If strCElluleC <> "" AND strCElluleD = "" Then
			oFeuille.getCellByPosition(2,iLigne).String	= ""
		endif 
		
		iLigne = iLigne+1
		
		strCEllule = oFeuille.getCellByPosition(0,iLigne).String
	Loop		


End Sub

Sub FabriqueDuPluriel ()

	Dim oDoc As Object, oFeuille As Object
	Dim strCEllule As String
	
	Dim strCelluleC As String, strCelluleD As String
	
	Dim iLigne As Integer
	
	
' On récupere le document
	oDoc = ThisComponent
' On récupere la feuille de LE mon document
	oFeuille = oDoc.Sheets.getByName("GENRE&NOMBRE")
	
	iLigne = 0
	
	strCEllule = oFeuille.getCellByPosition(0,iLigne).String

	
	Do While (strCEllule <> "")

		strCelluleC = oFeuille.getCellByPosition(2,iLigne).String
		strCelluleD = oFeuille.getCellByPosition(3,iLigne).String
		
		'' c'est du pluriel, on insere et copie et on vide
		If strCElluleD = "MP" OR strCElluleD = "FP"  OR strCElluleD = "NP" Then
		
			oFeuille.getRows.insertByIndex (iLigne+1,1)
			
			oFeuille.getCellByPosition(0,iLigne+1).String = strCElluleD
			oFeuille.getCellByPosition(1,iLigne+1).String = strCElluleC
			oFeuille.getCellByPosition(2,iLigne+1).String = oFeuille.getCellByPosition(1,iLigne).String
			
			oFeuille.getCellByPosition(2,iLigne).String = ""
			oFeuille.getCellByPosition(3,iLigne).String = ""
						
			iLigne = iLigne+1
		endif 
		
		iLigne = iLigne+1
		
		strCEllule = oFeuille.getCellByPosition(0,iLigne).String
	Loop		


End Sub

Sub VerifInvariables ()

	Dim oDoc As Object, oFeuille As Object
	Dim strCEllule As String
	
	Dim strCelluleA AS String
	
	Dim iLigne As Integer
	
	
' On récupere le document
	oDoc = ThisComponent
' On récupere la feuille de LE mon document
	oFeuille = oDoc.Sheets.getByName("GENRE&NOMBRE")
	
	iLigne = 0
	
	strCEllule = oFeuille.getCellByPosition(0,iLigne).String

	
	Do While (strCEllule <> "")

		if strCEllule = "NI" OR strCEllule = "MI" OR strCEllule = "FI" then
			oFeuille.getCellByPosition(2,iLigne).String = ""
			oFeuille.getCellByPosition(3,iLigne).String = ""
			oFeuille.getCellByPosition(4,iLigne).String = ""			
		endif 
		
		iLigne = iLigne+1
		
		strCEllule = oFeuille.getCellByPosition(0,iLigne).String
	Loop	
	

End Sub
