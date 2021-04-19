import PySimpleGUI as sg
import subprocess

layout = [[sg.Frame('Select Offensive Team(s)',[[sg.Checkbox('ARI',key='ARIO'),sg.Checkbox('ATL',key='ATLO'),sg.Checkbox('BUF',key='BUFO'),sg.Checkbox('BAL',key='BALO')],[sg.Checkbox('CAR',key='CARO'),sg.Checkbox('CIN',key='CINO'),sg.Checkbox('CLE',key='CLEO'),sg.Checkbox('CHI',key='CHIO')],[sg.Checkbox('DAL',key='DALO'),sg.Checkbox('DEN',key='DENO'),sg.Checkbox('DET',key='DETO'),sg.Checkbox('GB',key='GBO')],[sg.Checkbox('HOU',key='HOUO'),sg.Checkbox('IND',key='INDO'),sg.Checkbox('KC',key='KCO'),sg.Checkbox('LV',key='LVO')],[sg.Checkbox('LAC',key='LACO'),sg.Checkbox('LAR',key='LARO'),sg.Checkbox('JAX',key='JAXO'),sg.Checkbox('MIA',key='MIAO')],[sg.Checkbox('MIN',key='MINO'),sg.Checkbox('NE',key='NEO'),sg.Checkbox('NO',key='NOO'),sg.Checkbox('NYG',key='NYGO')],[sg.Checkbox('NYJ',key='NYJO'),sg.Checkbox('PHI',key='PHIO'),sg.Checkbox('SF',key='SFO'),sg.Checkbox('SEA',key='SEAO')],[sg.Checkbox('PIT',key='PITO'),sg.Checkbox('TB',key='TBO'),sg.Checkbox('TEN',key='TENO'),sg.Checkbox('WAS',key='WASO')]])
           ,sg.Frame('Select Defensive Team(s)',[[sg.Checkbox('ARI',key='ARID'),sg.Checkbox('ATL',key='ATLD'),sg.Checkbox('BUF',key='BUFD'),sg.Checkbox('BAL',key='BALD')],[sg.Checkbox('CAR',key='CARD'),sg.Checkbox('CIN',key='CIND'),sg.Checkbox('CLE',key='CLED'),sg.Checkbox('CHI',key='CHID')],[sg.Checkbox('DAL',key='DALD'),sg.Checkbox('DEN',key='DEND'),sg.Checkbox('DET',key='DETD'),sg.Checkbox('GB',key='GBD')],[sg.Checkbox('HOU',key='HOUD'),sg.Checkbox('IND',key='INDD'),sg.Checkbox('KC',key='KCD'),sg.Checkbox('LV',key='LVD')],[sg.Checkbox('LAC',key='LACD'),sg.Checkbox('LAR',key='LARD'),sg.Checkbox('JAX',key='JAXD'),sg.Checkbox('MIA',key='MIAD')],[sg.Checkbox('MIN',key='MIND'),sg.Checkbox('NE',key='NED'),sg.Checkbox('NO',key='NOD'),sg.Checkbox('NYG',key='NYGD')],[sg.Checkbox('NYJ',key='NYJD'),sg.Checkbox('PHI',key='PHID'),sg.Checkbox('SF',key='SFD'),sg.Checkbox('SEA',key='SEAD')],[sg.Checkbox('PIT',key='PITD'),sg.Checkbox('TB',key='TBD'),sg.Checkbox('TEN',key='TEND'),sg.Checkbox('WAS',key='WASD')]]),sg.Column([[sg.Frame('More Options',[[sg.Text('Quarter'),sg.Checkbox('1',key='Q1'),sg.Checkbox('2',key='Q2'),sg.Checkbox('3',key='Q3'),sg.Checkbox('4',key='Q4'),sg.Checkbox('OT',key='OT')],[sg.Checkbox('Touchdown Scored',key='scoreTD'),sg.Checkbox('First Down Gained',key='firstDown')]])],[sg.Text('Number of Top Plays to Display'),sg.Slider((5,25),key='numPlays')]]),sg.VerticalSeparator(),sg.Canvas(size=(10,5)),sg.Column([[sg.Button('Run')],[sg.Button('Exit')]])]
          ,[sg.Frame('Select Season(s)',[[sg.Checkbox('2018',key='2018')],[sg.Checkbox('2019',key='2019')],[sg.Checkbox('2020',key='2020')]]),sg.Frame('Value To Be Ranked By',[[sg.Radio('Most Yards Gained',1,key='mostYards'),sg.Radio('Least Yards Gained',1,key='leastYards'),sg.Radio('Earliest In Game',1,key='earlyGame'),sg.Radio('Latest In Game',1,key='lateGame'),sg.Radio('Most Yards From TD',1,key='mostTDYard')],[sg.Radio('Earliest Calendar Date',1,key='earlyCalDate'),sg.Radio('Latest Calendar Date',1,key='lateCalDate'),sg.Radio('Most Yards To First',1,key='mostYardFirst'),sg.Radio('Least Yards To First',1,key='leastYardFirst'),sg.Radio('Least Yards From TD',1,key='leastTDYard')]])]]

window = sg.Window('NFL Analysis', layout)

while True:
    event, values = window.read()
    if event is None or event == 'Exit':
        break
    if event == 'Run':
        season = int(values['2018']) + 2*values['2019'] + 4*values['2020']
        if season == 0:
            sg.popup_error('Invalid Season Selection:','Must select at least 1 season',title='Error')
            continue
        offensiveTeams = int(values['ARIO']) +2*values['ATLO'] + 4*values['BUFO'] + 8*values['BALO'] + 16*values['CARO'] + 32*values['CINO'] + 64*values['CLEO'] + 128*values['CHIO'] + 256*values['DALO'] + 512*values['DENO'] + 1024*values['DETO'] + 2048*values['GBO'] + 4096*values['HOUO'] + 8192*values['INDO'] + 16384*values['KCO'] + 32768*values['LVO'] + 65536*values['LACO'] + 131072*values['LARO'] + 262144*values['JAXO'] + 524288*values['MIAO'] + 1048576*values['MINO'] + 2097152*values['NEO'] + 4194304*values['NOO'] + 8388608*values['NYGO'] + 16777216*values['NYJO'] + 33554432*values['PHIO'] + 67108864*values['SFO'] + 134217728*values['SEAO'] + 268435456*values['PITO'] + 536870912*values['TBO'] + 1073741824*values['TENO'] + 2147483648*values['WASO']
        defensiveTeams = int(values['ARID']) + 2*values['ATLD'] + 4*values['BUFD'] + 8*values['BALD'] + 16*values['CARD'] + 32*values['CIND'] + 64*values['CLED'] + 128*values['CHID'] + 256*values['DALD'] + 512*values['DEND'] + 1024*values['DETD'] + 2048*values['GBD'] + 4096*values['HOUD'] + 8192*values['INDD'] + 16384*values['KCD'] + 32768*values['LVD'] + 65536*values['LACD'] + 131072*values['LARD'] + 262144*values['JAXD'] + 524288*values['MIAD'] + 1048576*values['MIND'] + 2097152*values['NED'] + 4194304*values['NOD'] + 8388608*values['NYGD'] + 16777216*values['NYJD'] + 33554432*values['PHID'] + 67108864*values['SFD'] + 134217728*values['SEAD'] + 268435456*values['PITD'] + 536870912*values['TBD'] + 1073741824*values['TEND'] + 2147483648*values['WASD']
        if offensiveTeams == 0 or defensiveTeams == 0:
            sg.popup_error('Invalid Team Selection:','Must select at least 1 team','for offense and defense',title='Error')
            continue
        rankVal = int(values['mostYards']) + 2*values['leastYards'] + 4*values['earlyGame'] + 8*values['lateGame'] + 16*values['earlyCalDate'] + 32*values['lateCalDate'] + 64*values['mostYardFirst'] + 128*values['leastYardFirst'] + 256*values['mostTDYard'] + 512*values['leastTDYard']
        if rankVal == 0:
            sg.popup_error('Invalid Ranking Value Selection:', 'Must select at least 1 ranking value', title='Error')
            continue
        firstDown = int(values['firstDown'])
        scoreTD = int(values['scoreTD'])
        quarter = int(values['Q1']) + 2*values['Q2'] + 4*values['Q3'] + 8*values['Q4'] + 16*values['OT']
        if quarter == 0:
            sg.popup_error('Invalid Quarter Selection:', 'Must select at least 1 quarter', title='Error')
            continue
        numPlays = values['numPlays']
        sg.popup_auto_close("Please be patient, program running",title='Info')
        sub = subprocess.run(args=['proj3.out',str(season),str(offensiveTeams),str(defensiveTeams),str(rankVal),str(quarter),str(firstDown),str(scoreTD),str(numPlays)], capture_output=True)
        text = sub.stdout.decode()
        sg.popup_scrolled(text,title='Requested Analysis',size=(100,25))

window.close()